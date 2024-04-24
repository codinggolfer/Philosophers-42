/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:09:21 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/24 14:51:43 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	thinking(t_philo *philo)
{
	print_status(THINKING, philo);
}

static void	de_sync_philos(t_philo *philo)
{
	if (philo->data->nbr_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(30);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo);
	}
}

static void	eating(t_philo *philo)
{
	locker(&philo->first_fork->fork);
	print_status(TAKE_F_FORK, philo);
	locker(&philo->second_fork->fork);
	print_status(TAKE_S_FORK, philo);
	set_value(&philo->data->time_mutex,
		&philo->last_meal_time, get_exact_time());
	philo->meal_counter++;
	print_status(EATING, philo);
	ft_usleep(philo->data->eat);
	unlocker(&philo->first_fork->fork);
	unlocker(&philo->second_fork->fork);
}

void	*main_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all(philo->data);
	set_value(&philo->data->time_mutex,
		&philo->last_meal_time, get_exact_time());
	// if (philo->id % 2 == 0)
	// 	thinking(philo);
	de_sync_philos(philo);
	while (1)
	{
		eating(philo);
		locker(&philo->data->data_mutex);
		if ((philo->data->nbr_of_meals == philo->meal_counter
				&& philo->data->nbr_of_meals) || philo->data->dead == 1)
		{
			unlocker(&philo->data->data_mutex);
			break ;
		}
		unlocker(&philo->data->data_mutex);
		print_status(SLEEPING, philo);
		ft_usleep(philo->data->sleep);
		thinking(philo);
	}
	return (NULL);
}
