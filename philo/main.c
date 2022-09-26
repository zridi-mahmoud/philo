/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:28:42 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/25 22:23:56 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_philo(t_philo **philos)
{
	pthread_mutex_destroy((*philos)[0].params->forks);
	pthread_mutex_destroy(&(*philos)[0].params->print);
	free((*philos)[0].params->forks);
	free_philos(0, philos, (*philos)[0].params);
}

void	lunch_threads(t_philo **philos, pthread_t *threads)
{
	int	i;
	int	n;

	i = -1;
	n = (*philos)[0].params->n_philo;
	while (++i < (*philos)[0].params->n_philo)
		pthread_create(threads + i, NULL, &routine, philos[i]);
	while (1)
	{
		if (philos[i % n]->params->check_n_eat && \
		philos[i % n]->params->n_philo == philos[i % n]->params->i_must_eat)
		{	
			pthread_mutex_lock(&(philos[i % n]->params->print));
			break ;
		}
		if (get_time(philos[i % n]->params) - philos[i % n]->last_eat >= \
			philos[i % n]->params->t_die)
		{
			pthread_mutex_lock(&(philos[i % n]->params->print));
			printf("%lld %d died\n", get_time(philos[i % n]->params), \
				philos[i % n]->n);
			break ;
		}
		i = (i + 1) % n;
	}
}

int	main(int argc, char **argv)
{
	t_philo		**philos;
	pthread_t	*treads;
	t_params	*params;

	params = NULL;
	philos = NULL;
	params = parse_input(argv, argc);
	if (!params)
		return (printf("Error\n"), 1);
	treads = malloc(params->n_philo * sizeof(pthread_t));
	if (!treads)
		return (free(params), 1);
	philos = init_philos(philos, params);
	params->keep_going = 1;
	if (params->check_n_eat && !params->n_must_eat)
		return (exit_philo(philos), 0);
	lunch_threads(philos, treads);
	free(treads);
	params->keep_going = 0;
	exit_philo(philos);
}
