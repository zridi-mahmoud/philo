/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:52:12 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/25 14:34:26 by mzridi           ###   ########.fr       */
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

int	printer(t_philo	*philo, int type)
{
	pthread_mutex_lock(&philo->params->print);
	if (type == 0)
		printf("%lld %d has taken a fork left\n", get_time(philo->params), philo->n);
	if (type == 1)
		printf("%lld %d has taken a fork right\n", get_time(philo->params), philo->n);
	if (type == 1)
		printf("%lld %d is eating\n", get_time(philo->params), philo->n);
	if (type == 2)
		printf("%lld %d is sleeping\n", get_time(philo->params), philo->n);
	else if (type == 3)
		printf("%lld %d is thinking\n", get_time(philo->params), philo->n);
	pthread_mutex_unlock(&philo->params->print);
	return (0);
}

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (1)
	{
		if ((philo->n % 2 == 1 && philo->n < philo->params->n_philo) || philo->params->start >= philo->params->n_philo / 2)
		{	
			pthread_mutex_lock(philo->left);
			if (printer(philo, 0))
				return (NULL);
			pthread_mutex_lock(philo->right);
			if (printer(philo, 1))
				return (NULL);
			printf("%d ------------%lld\n",philo->n, get_time(philo->params));
			usleep((philo->params->t_eat)*1000);
			printf("%d ------------%lld\n",philo->n, get_time(philo->params));
			philo->last_eat = get_time(philo->params);
			philo->eaten += 1;
			if (philo->eaten == philo->params->n_must_eat)
				philo->params->i_must_eat +=1;
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
			if (printer(philo, 2))
				return (NULL);
			philo->params->start += 1;
			printf("%d ------------%lld\n",philo->n, get_time(philo->params));
			usleep((philo->params->t_sleap)*1000);
			printf("%d ------------%lld\n",philo->n, get_time(philo->params));
			if (printer(philo, 3))
				return (NULL);
			pthread_mutex_unlock(&philo->params->print);
		}
	}
	return (NULL);
}


// void	*routine(void *v_philo)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)v_philo;
// 	while (1)
// 	{
// 		if (philo->n % 2 == 0 || philo->params->start >= philo->params->n_philo / 2)
// 		{	
// 			pthread_mutex_lock(philo->left);
			
// 			pthread_mutex_lock(&philo->params->print);
// 			if (philo->params->should_stop)
// 				return (pthread_mutex_unlock(&philo->params->print), pthread_mutex_unlock(philo->left), NULL);
// 			printf("%lld %d has taken a fork left\n", get_time(philo->params), philo->n);
// 			pthread_mutex_unlock(&philo->params->print);
			
// 			pthread_mutex_lock(philo->right);
			
// 			pthread_mutex_lock(&philo->params->print);
// 			if (philo->params->should_stop)
// 				return (pthread_mutex_unlock(&philo->params->print), pthread_mutex_unlock(philo->left), pthread_mutex_unlock(philo->right), NULL);
// 			printf("%lld %d has taken a fork right\n", get_time(philo->params), philo->n);
// 			pthread_mutex_unlock(&philo->params->print);

// 			pthread_mutex_lock(&philo->params->print);
// 			if (philo->params->should_stop)
// 				return (pthread_mutex_unlock(&philo->params->print), pthread_mutex_unlock(philo->left), pthread_mutex_unlock(philo->right), NULL);
// 			printf("%lld %d is eating\n", get_time(philo->params), philo->n);
// 			pthread_mutex_unlock(&philo->params->print);
// 			usleep(philo->params->t_eat);
// 			philo->last_eat = get_time(philo->params);
// 			philo->eaten += 1;
// 			if (philo->eaten == philo->params->n_must_eat)
// 				philo->params->i_must_eat +=1;
// 			pthread_mutex_unlock(philo->left);
// 			pthread_mutex_unlock(philo->right);
// 			pthread_mutex_lock(&philo->params->print);
// 			if (philo->params->should_stop)
// 				return (pthread_mutex_unlock(&philo->params->print), NULL);
// 			printf("%lld %d is sleeping\n", get_time(philo->params), philo->n);
// 			pthread_mutex_unlock(&philo->params->print);
// 			philo->params->start += 1;
// 			usleep(philo->params->t_sleap);
// 			pthread_mutex_lock(&philo->params->print);
// 			if (philo->params->should_stop)
// 				return (pthread_mutex_unlock(&philo->params->print), NULL);
// 			printf("%lld %d is thinking\n", get_time(philo->params), philo->n);
// 			pthread_mutex_unlock(&philo->params->print);
// 		}
// 	}
// 	return (NULL);
// }
