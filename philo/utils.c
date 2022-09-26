/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:52:12 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/25 21:36:48 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(t_params *params)
{
	struct timeval	tv;
	long long		time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	return (time_in_mill - params->start_time);
}

void	ft_usleep(long long time, t_params *params)
{
	long long	start;

	usleep((int)(time * (9 / 10)));
	start = get_time(params) * 1000;
	while (get_time(params) * 1000 < start + time)
	{
		usleep(50);
	}
}

void	printer(t_philo	*philo, int type)
{
	pthread_mutex_lock(&philo->params->print);
	if (type == 0)
		printf("%lld %d has taken a fork left\n", \
			get_time(philo->params), philo->n);
	if (type == 1)
		printf("%lld %d has taken a fork right\n", \
			get_time(philo->params), philo->n);
	if (type == 1)
		printf("%lld %d is eating\n", get_time(philo->params), philo->n);
	if (type == 2)
		printf("%lld %d is sleeping\n", get_time(philo->params), philo->n);
	else if (type == 3)
		printf("%lld %d is thinking\n", get_time(philo->params), philo->n);
	pthread_mutex_unlock(&philo->params->print);
	if (type == 2)
	{
		philo->params->start += 1;
		ft_usleep(philo->params->t_sleap * 1000, philo->params);
		printer(philo, 3);
	}
}

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	philo->last_eat = get_time(philo->params);
	while (philo->params->keep_going)
	{
		if ((philo->n % 2 == 1 && philo->n < philo->params->n_philo) || \
		philo->params->start >= philo->params->n_philo / 2)
		{	
			pthread_mutex_lock(philo->left);
			printer(philo, 0);
			pthread_mutex_lock(philo->right);
			printer(philo, 1);
			ft_usleep(philo->params->t_eat * 1000, philo->params);
			philo->last_eat = get_time(philo->params);
			philo->eaten += 1;
			if (philo->eaten == philo->params->n_must_eat)
				philo->params->i_must_eat += 1;
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			printer(philo, 2);
		}
	}
	return (NULL);
}
