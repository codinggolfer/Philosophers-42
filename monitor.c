/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:03:20 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/15 17:32:33 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *moni)
{

}

int	check_full(t_philo *moni)
{
	int	i;

	i = 0;
	if (!moni->data->nbr_of_meals)
		return (0);
	while (i < moni->data->nbr_of_philos)
	{
		pthread_mutex_lock(&moni[i].meal_lock);
		moni->data.
	}
}

void	*monitor(void *arg)
{
	t_philo	*moni;

	moni = (t_philo *)arg;
	while (1)
	{
		if (check_dead(moni) == 1 || check_full(moni) == 1)
			break;
	}
	return (arg);
}