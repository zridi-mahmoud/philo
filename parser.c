/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:57:54 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/13 22:22:01 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_params(t_params *params, char **argv, int argc)
{
	long long	tmp;

	if (!(argc == 5 || argc == 6))
		return (0);
	tmp = ft_atoi(argv[1]);
	if (tmp > (1L<<31) - 1)
		return (0);
	params->n_philo = tmp;
		tmp = ft_atoi(argv[2]);
	if (tmp > (1L<<31) - 1)
		return (0);
	params->t_die = tmp;
	tmp = ft_atoi(argv[3]);
	if (tmp > (1L<<31) - 1)
		return (0);
	params->t_eat = tmp;
	tmp = ft_atoi(argv[4]);
	if (tmp > (1L<<31) - 1)
		return (0);
	params->t_sleap = tmp;
	return (1);
}

t_params	*parse_input(char **argv, int argc)
{
	t_params	*params;
	long		tmp;

	params = (t_params *)malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	if (!get_params(params, argv, argc))
		return (free(params) ,NULL);
	if (argc == 6)
	{
		tmp = ft_atoi(argv[5]);
		if (tmp > (long)(1<<31) -1)
			return (free(params) ,NULL);
		params->n_philo = tmp;
	}
	return (params);
}
