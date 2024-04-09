/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:43:04 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/09 19:55:49 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_status status, t_philo *philo)
{
	long	time_passed;

	time_passed = get_current_time();
	pthread_mutex_lock(&philo->data->print_mutex);
	if (status == TAKE_F_FORK || status == TAKE_S_FORK)
		printf("%ld %d has taken a fork\n", time_passed, philo->id);
	else if (status == EATING)
		printf("%ld %d is eating\n", time_passed, philo->id);
	else if (status == SLEEPING)
		printf("%ld %d is sleeping\n", time_passed, philo->id);
	else if (status == THINKING)
		printf("%ld %d is thinking\n", time_passed, philo->id);
	else if (status == DIED)
		printf("%ld %d has died\n", time_passed, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}