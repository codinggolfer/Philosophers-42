/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:05:10 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/17 16:31:48 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_finished(t_data *moni)
{
	if (moni->full == 1)
		return (0);
	pthread_mutex_lock(&moni->data_mutex);
	if (moni->dead == 1)
	{
		pthread_mutex_unlock(&moni->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&moni->data_mutex);
	return (0);
}

static int	philo_died(t_philo *philo)
{
	long	passed;

	passed = get_current_time();
	if (philo->data->full == 1)
		return (0);
	if (passed - philo->last_meal_time >= philo->data->time_to_die)
		return (1);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*moni;
	int		i;

	moni = (t_data *) arg;
	while (1)
	{
		pthread_mutex_lock(&moni->philos->philo_mutex);
		if (moni->philos->philo_threads == moni->nbr_of_philos)
			break ;
		pthread_mutex_lock(&moni->philos->philo_mutex);
	}
	while (!sim_finished(moni))
	{
		i = 0;
		while (i < moni->nbr_of_philos && !sim_finished(moni))
		{
			if (philo_died(moni->philos + i) == 1)
			{
				print_status(DIED, moni->philos + i);
				moni->dead = 1;
			}
			i++;
		}
		if (moni->full == 1)
			break ;
	}
	return (NULL);
}