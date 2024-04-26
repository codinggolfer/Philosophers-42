/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:42:38 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/26 15:04:26 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	add_input(t_data *philo, char **arg)
{
	philo->nbr_of_philos = ft_atol(arg[1]);
	philo->time_to_die = ft_atol(arg[2]);
	philo->eat = ft_atol(arg[3]);
	philo->sleep = ft_atol(arg[4]);
	if (arg[5])
		philo->nbr_of_meals = ft_atol(arg[5]);
}

int	arg_check(char **arg)
{
	if (ft_atol(arg[1]) > PHILO_MAX || ft_atol(arg[1]) <= 0 || \
		check_digit(arg[1]) == 1)
		return (printf("Invalid amount of philosophers\n"));
	if (ft_atol(arg[2]) <= 0 || check_digit(arg[2]) == 1)
		return (printf("Invalid time to die\n"));
	if (ft_atol(arg[3]) <= 0 || check_digit(arg[3]) == 1)
		return (printf("Philosopher doesn't know when to eat\n"));
	if (ft_atol(arg[4]) <= 0 || check_digit(arg[4]) == 1)
		return (printf("Philosopher's sleeping schedule is invalid\n"));
	if (arg[5] && (ft_atol(arg[5]) < 0 || check_digit(arg[5]) == 1))
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
		add_input(&philo, av);
		data_init(&philo);
		if (!(philo.philos) || !(philo.forks))
		{
			if (philo.philos)
				free (philo.philos);
			return (1);
		}
		if (philo.nbr_of_philos == 1)
			lone_philo(philo.philos);
		else
			table_is_ready(&philo);
		free_all(&philo);
	}
	else
		printf("Wrong amount of arguments\n");
}
