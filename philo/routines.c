/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:09:21 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/19 14:39:06 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	print_status(THINKING, philo);
	ft_usleep(50);
}

/*grab the first and the second fork
  eat : write eating, update last meal, meal counter
  release th forks in the end*/
static void	eating(t_philo *philo)
{
	locker(&philo->first_fork->fork);
	print_status(TAKE_F_FORK, philo);
	locker(&philo->second_fork->fork);
	print_status(TAKE_S_FORK, philo);
	set_value(&philo->data->time_mutex, &philo->last_meal_time, get_exact_time());
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
	set_value(&philo->data->time_mutex, &philo->last_meal_time, get_exact_time());
	if (philo->id % 2 == 0)
		thinking(philo);
	while (1)
	{
		eating(philo);
		pthread_mutex_lock(&philo->data->data_mutex);
		if ((philo->data->nbr_of_meals == philo->meal_counter
				&& philo->data->nbr_of_meals) || philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		print_status(SLEEPING, philo);
		ft_usleep(philo->data->sleep);
		thinking(philo);
	}
	return (NULL);
}