/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:06:02 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/26 14:37:47 by eagbomei         ###   ########.fr       */
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
	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("mutex failed\n");
		return ;
	}
}

void	unlocker(t_mtx *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("mutex failed\n");
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
