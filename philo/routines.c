/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:09:21 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/18 18:33:58 by eagbomei         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->first_fork->fork);
	print_status(TAKE_F_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_status(TAKE_S_FORK, philo);
	pthread_mutex_lock(&philo->data->time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->time_mutex);
	philo->meal_counter++;
	print_status(EATING, philo);
	ft_usleep(philo->data->eat);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*main_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all(philo->data);
	pthread_mutex_lock(&philo->data->time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->time_mutex);
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