/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:09:21 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/26 15:11:49 by eagbomei         ###   ########.fr       */
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
			thinking(philo);
	}
	else
	{
		if (philo->id % 2)
			ft_usleep(30);
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
	locker(&philo->data->data_mutex);
	philo->meal_counter++;
	unlocker(&philo->data->data_mutex);
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
