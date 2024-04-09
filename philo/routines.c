/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:09:21 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/09 19:56:59 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// static void	get_forks(t_philo *philo)
// {
	
// }
static void	thinking(t_philo *philo)
{
	print_status(THINKING, philo);
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
	philo->last_meal_time = philo->data->start - get_current_time();
	if (philo->last_meal_time > philo->data->time_to_die)
	{
		print_status(DIED, philo);
	}
	philo->meal_counter++;
	print_status(EATING, philo);
	ft_usleep(philo->data->eat);
	if (philo->meal_counter == philo->data->nbr_of_meals && philo->data->nbr_of_meals)
		return ; // if filos have eaten enought return function thing...
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*main_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	//wait_all(philo->data);
	exit(0);
	while (1)
	{
		if (philo->data->nbr_of_meals == 0 && philo->data->nbr_of_meals)
			break ;
		eating(philo);
		print_status(SLEEPING, philo);
		ft_usleep(philo->data->sleep);
		thinking(philo);
	}
	return (NULL);
}