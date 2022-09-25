/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:28:42 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/25 13:49:15 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_philo(t_philo **philos)
{
	pthread_mutex_destroy((*philos)[0].params->forks);
}

void	lunch_threads(t_philo **philos, pthread_t *threads)
{
	int	i;
	int	n;

	i = -1;
	n = (*philos)[0].params->n_philo;
	while (++i < (*philos)[0].params->n_philo)
		pthread_create(threads + i, NULL, &routine, philos[i]);
	while (!(*philos)[0].params->should_stop)
	{
		// printf("%d\n",philos[1]->params->n_philo);
		if (philos[i%n]->params->check_n_eat && philos[i%n]->params->n_philo == philos[i%n]->params->i_must_eat)
		{	
			pthread_mutex_lock(&(philos[i%n]->params->print));
			(*philos)[0].params->should_stop = 1;
			break;
		}
		if (get_time(philos[i%n]->params) - philos[i%n]->last_eat >= philos[i%n]->params->t_die)
		{
			pthread_mutex_lock(&(philos[i%n]->params->print));
			printf("%lld %d died\n", get_time(philos[i%n]->params), philos[i%n]->n);
			philos[i%n]->params->should_stop = 1;
			break ;
		}
		i++;
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
	lunch_threads(philos, treads);
	exit_philo(philos);
}
