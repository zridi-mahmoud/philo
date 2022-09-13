/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:59:01 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/13 22:03:11 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

typedef	struct	s_globl_params {
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleap;
	int	n_must_eat;
}	t_params;

long	ft_atoi(const char *str);
t_params	*parse_input(char **args, int argc);

#endif