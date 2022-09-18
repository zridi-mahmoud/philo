/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:28:42 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/17 00:52:33 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lunch_threads(t_philo **philos, pthread_t *threads)
{
	int			i;

	i = -1;
	while (++i < (*philos)[0].params->n_philo)
		pthread_create(threads + i, NULL, &routine, philos[i]);
	i = 0;
	while (i < (*philos)[0].params->n_philo)
		pthread_join(threads[i], NULL);
	return (1);
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
}
