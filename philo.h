/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:59:01 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/16 22:53:37 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<pthread.h>
# include <sys/time.h>

typedef struct s_globl_params {
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleap;
	int				n_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				start;
	long long		start_time;
}	t_params;

typedef struct s_philo {
	int				n;
	double			last_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_params		*params;
}	t_philo;

long		ft_atoi(const char *str);
t_params	*parse_input(char **args, int argc);
t_philo		**init_philos(t_philo **philos, t_params *params);
void		*routine(void *philo);
long long	get_time(t_params *params);

#endif