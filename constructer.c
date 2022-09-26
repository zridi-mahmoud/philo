/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:57:54 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/25 22:39:28 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_params(t_params *params, char **argv, int argc)
{
	long long	tmp;

	if (!(argc == 5 || argc == 6))
		return (0);
	tmp = ft_atoi(argv[1]);
	if (tmp > (1L << 31) - 1 || tmp <= 0)
		return (0);
	params->n_philo = tmp;
		tmp = ft_atoi(argv[2]);
	if (tmp > (1L << 31) - 1 || tmp < 0)
		return (0);
	params->t_die = tmp;
	tmp = ft_atoi(argv[3]);
	if (tmp > (1L << 31) - 1 || tmp < 0)
		return (0);
	params->t_eat = tmp;
	tmp = ft_atoi(argv[4]);
	if (tmp > (1L << 31) - 1 || tmp < 0)
		return (0);
	params->t_sleap = tmp;
	params->start = 0;
	params->forks = malloc(params->n_philo * sizeof(pthread_mutex_t));
	if (!params->forks)
		return (0);
	return (1);
}

t_params	*parse_input(char **argv, int argc)
{
	t_params		*params;
	long			tmp;
	struct timeval	tv;
	long long		time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	params = (t_params *)malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	params->check_n_eat = 0;
	if (!get_params(params, argv, argc))
		return (free(params), NULL);
	if (argc == 6)
	{
		tmp = ft_atoi(argv[5]);
		if (tmp > (1L << 31) - 1 || tmp < 0)
			return (free(params), NULL);
		params->n_must_eat = tmp;
		params->check_n_eat = 1;
	}
	params->start_time = time_in_mill;
	if (pthread_mutex_init(&params->print, NULL))
		return (free(params), NULL);
	return (params);
}

void	free_philos(int n, t_philo **philos, t_params *params)
{
	while (n < params->n_philo)
	{
		free(philos[n++]);
	}
	free(philos);
	free(params);
}

t_philo	**init_philos(t_philo **philos, t_params *params)
{
	int	n;
	int	mtx;

	n = params->n_philo;
	mtx = 0;
	philos = malloc(n * sizeof(t_philo *));
	if (!philos)
		return (free(params), NULL);
	while (n--)
	{
		philos[n] = malloc(sizeof(t_philo));
		mtx = pthread_mutex_init(&params->forks[n], NULL);
		if (!philos[n])
			return (free_philos(n + 1, philos, params), NULL);
		philos[n]->n = n + 1;
		philos[n]->left = &params->forks[n];
		philos[n]->right = &params->forks[(n + 1) % params->n_philo];
		philos[n]->params = params;
		philos[n]->last_eat = get_time(params);
		philos[n]->eaten = 0;
	}
	return (philos);
}
