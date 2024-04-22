/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lone_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:46:52 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/22 15:36:12 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	*lone_routine(void *loner)
{
	t_philo	*philo;

	philo = (t_philo *)loner;
	wait_all(philo->data);
	set_value(&philo->data->time_mutex, &philo->last_meal_time, get_exact_time());
	locker(&philo->first_fork->fork);
	print_status(TAKE_F_FORK, philo);
	while (1)
	{
		locker(&philo->data->data_mutex);
		if (philo->data->dead == 1)
		{
			unlocker(&philo->data->data_mutex);
			break ;
		}
		unlocker(&philo->data->data_mutex);
	}
	unlocker(&philo->first_fork->fork);
	return (NULL);
}

void	lone_philo(t_philo *philo)
{
	pthread_t	moni;

	if (pthread_create(&philo[0].thread_id, NULL, lone_routine, &philo[0]) != 0)
	{
			/*error stuff here return and destroy mlx*/
			return ;
	}
	if (pthread_create(&moni, NULL, monitor, philo->data) != 0)
	{
			/*error stuff here return and destroy mlx*/
			return ;
	}
	philo->data->start = get_exact_time();
	locker(&philo->philo_mutex);
	philo->data->threads_ready = true;
	unlocker(&philo->philo_mutex);
	if (!join_threads(philo->data))
		return ;
	pthread_join(moni, NULL);

}
