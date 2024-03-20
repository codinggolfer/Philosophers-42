/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:42:38 by eagbomei          #+#    #+#             */
/*   Updated: 2024/03/20 17:04:52 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_check(char **arg)
{
	if (ft_atoi(arg[1]) > PHILO_MAX || ft_atoi(arg[1]) <= 0 || \
		check_digit(arg[1]) == 1)
		return (printf("Invalid amount of philosophers\n"));
	if (ft_atoi(arg[2]) <= 0 || check_digit(arg[2]) == 1)
		return (printf("Invalid time to die\n"));
	if (ft_atoi(arg[3]) <= 0 || check_digit(arg[3]) == 1)
		return (printf("Philosopher doesn't know when to eat\n"));
	if (ft_atoi(arg[4]) <= 0 || check_digit(arg[4]) == 1)
		return (printf("Philosopher's sleeping schedule is invalid\n"));
	if (arg[5] && (ft_atoi(arg[5]) < 0 || check_digit(arg[5]) == 1))
		return (printf("Invalid amount of lunches\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	philo;

	if (ac == 5 || ac == 6)
	{
		if (arg_check(av) != 0)
			return (1);
	}
	else
		printf("Wrong amount of arguments\n");
}