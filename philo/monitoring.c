/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:05:10 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/26 14:37:11 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_finished(t_data *moni)
{
	locker(&moni->data_mutex);
	if (moni->full == 1)
	{
		unlocker(&moni->data_mutex);
		return (0);
	}
	if (moni->dead == 1)
	{
		unlocker(&moni->data_mutex);
		return (1);
	}
	unlocker(&moni->data_mutex);
	return (0);
}

static int	philo_died(t_philo *philo)
{
	long	passed;

	set_value(&philo->data->time_mutex, &passed, get_exact_time());
	locker(&philo->data->data_mutex);
	if (philo->meal_counter == philo->data->nbr_of_meals
		&& philo->data->nbr_of_meals)
	{
		unlocker(&philo->data->data_mutex);
		return (0);
	}
	unlocker(&philo->data->data_mutex);
	locker(&philo->data->time_mutex);
	if (passed - philo->last_meal_time > philo->data->time_to_die)
	{
		unlocker(&philo->data->time_mutex);
		return (1);
	}
	unlocker(&philo->data->time_mutex);
	return (0);
}

static void	monitor_ready_to_go(t_data *moni)
{
	while (1)
	{
		locker(&moni->philo_mutex);
		if (moni->philos->philo_threads == moni->nbr_of_philos)
		{
			unlocker(&moni->philo_mutex);
			break ;
		}
		unlocker(&moni->philo_mutex);
	}
}

void	*monitor(void *arg)
{
	t_data	*moni;
	int		i;

	moni = (t_data *) arg;
	monitor_ready_to_go(moni);
	while (!sim_finished(moni))
	{
		i = 0;
		while (i < moni->nbr_of_philos && !sim_finished(moni))
		{
			if (philo_died(moni->philos + i) == 1 && moni->detach != 1)
			{
				print_status(DIED, moni->philos + i);
				set_value(&moni->data_mutex, &moni->dead, 1);
			}
			i++;
		}
		if (check_available(&moni->data_mutex, moni->full) == 1)
			break ;
	}
	return (NULL);
}
