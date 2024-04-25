/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:06:02 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/25 13:59:26 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_value(t_mtx *mutex, long *value, long time)
{
	locker(mutex);
	*value = time;
	unlocker(mutex);
}

void	locker(t_mtx *mutex)
{
	t_data	philo;

	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("mutex failed\n");
		philo.detach = 1;
		return ;
	}
}

void	unlocker(t_mtx *mutex)
{
	t_data	philo;

	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("mutex failed\n");
		philo.detach = 1;
		return ;
	}
}

int	check_available(t_mtx *mutex, long value)
{
	locker(mutex);
	if (value == 1)
	{
		unlocker(mutex);
		return (1);
	}
	unlocker(mutex);
	return (value);
}
