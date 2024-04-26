/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lone_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:46:52 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/26 15:10:19 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*lone_routine(void *loner)
{
	t_philo	*philo;

	philo = (t_philo *)loner;
	set_value(&philo->data->time_mutex,
		&philo->last_meal_time, get_exact_time());
	locker(&philo->first_fork->fork);
	print_status(TAKE_F_FORK, philo);
	unlocker(&philo->first_fork->fork);
	ft_usleep(philo->data->time_to_die);
	print_status(DIED, philo);
	return (NULL);
}

void	lone_philo(t_philo *philo)
{
	if (pthread_create(&philo[0].thread_id, NULL, lone_routine, &philo[0]) != 0)
	{
		write (2, "error in lone philo create\n", 28);
		return ;
	}
	locker(&philo->data->time_mutex);
	philo->data->start = get_exact_time();
	unlocker(&philo->data->time_mutex);
	pthread_join(philo->thread_id, NULL);
	return ;
}
