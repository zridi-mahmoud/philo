/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:52:12 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/17 00:55:29 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(t_params *params)
{
	struct timeval	tv;
	long long		time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	return (time_in_mill - params->start);
}

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (1)
	{
		if (philo->n % 2 == 0 || philo->params->start > philo->params->n_must_eat / 2)
		{	
			// lock lef 
			pthread_mutex_lock(philo->left);
			pthread_mutex_lock(&philo->params->print);
			printf("philo %d locked %p\n", philo->n, philo->left);
			printf("%lld %d has taken a fork left\n", get_time(philo->params), philo->n);
			pthread_mutex_unlock(&philo->params->print);
			// lock right
			pthread_mutex_lock(philo->right);
			printf("philo %d locked %p\n", philo->n, philo->right);
			pthread_mutex_lock(&philo->params->print);
			printf("%lld %d has taken a fork right\n", get_time(philo->params), philo->n);
			pthread_mutex_unlock(&philo->params->print);

			pthread_mutex_lock(&philo->params->print);
			printf("%lld %d is eating\n", get_time(philo->params), philo->n);
			pthread_mutex_unlock(&philo->params->print);

			usleep(philo->params->t_eat);
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			pthread_mutex_lock(&philo->params->print);
			printf("%lld %d is sleeping\n", get_time(philo->params), philo->n);
			pthread_mutex_unlock(&philo->params->print);
			usleep(philo->params->t_sleap);
			pthread_mutex_lock(&philo->params->print);
			philo->params->start += 1;
			printf("%lld %d is thinking\n", get_time(philo->params), philo->n);
			pthread_mutex_unlock(&philo->params->print);
		}
	}
	return (NULL);
}
