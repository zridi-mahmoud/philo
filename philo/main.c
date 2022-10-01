/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:28:42 by mzridi            #+#    #+#             */
/*   Updated: 2022/10/01 16:30:42 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_philo(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < (*philos)->params->n_philo)
	{
		pthread_mutex_destroy((*philos)[0].params->forks + i);
		i++;
	}
	pthread_mutex_destroy(&((*philos)[0].params->print));
	free((*philos)[0].params->forks);
	free_philos(0, philos, (*philos)[0].params);
}

void	check_stop_condition(t_philo	**philos)
{
	int	i;
	int	n;

	i = 0;
	n = (*philos)[0].params->n_philo;
	while (1)
	{
		if (philos[i]->params->check_n_eat && \
		philos[i]->params->n_philo == philos[i]->params->i_must_eat)
		{	
			pthread_mutex_lock(&(philos[i]->params->print));
			break ;
		}
		if (get_time(philos[i]->params) - philos[i]->last_eat >= \
			philos[i]->params->t_die)
		{
			pthread_mutex_lock(&(philos[i]->params->print));
			printf("%lld %d died\n", get_time(philos[i]->params), \
				philos[i]->n);
			break ;
		}
		i = (i + 1) % n;
	}
}

void	lunch_threads(t_philo **philos, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < (*philos)[0].params->n_philo)
	{
		if (pthread_create(threads + i, NULL, &routine, philos[i]))
		{
			if (i > 0)
				(*philos)[0].params->keep_going = 0;
			return ;
		}
	}
	check_stop_condition(philos);
	i = -1;
	while (++i < (*philos)[0].params->n_philo)
		pthread_detach(threads[i]);
}

int	main(int argc, char **argv)
{
	t_philo		**philos;
	pthread_t	*threads;
	t_params	*params;

	params = NULL;
	philos = NULL;
	params = parse_input(argv, argc);
	if (!params)
		return (printf("Error\n"), 1);
	threads = malloc(params->n_philo * sizeof(pthread_t));
	if (!threads)
		return (free(params), 1);
	philos = init_philos(philos, params);
	params->keep_going = 1;
	if (params->check_n_eat && !params->n_must_eat)
		return (exit_philo(philos), 0);
	lunch_threads(philos, threads);
	usleep(100);
	free(threads);
	params->keep_going = 0;
	exit_philo(philos);
}
