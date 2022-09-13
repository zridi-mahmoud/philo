/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:28:42 by mzridi            #+#    #+#             */
/*   Updated: 2022/09/13 22:25:12 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_params    *params;

	params = parse_input(argv, argc);
	if (!params)
		return (printf("Error\n"), 1);
	printf("%d\n", params->n_philo);
	printf("t_die %d\n", params->t_eat);
}