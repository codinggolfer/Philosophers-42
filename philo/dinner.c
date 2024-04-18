/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:40:25 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/18 18:32:25 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &main_routine,
				&data->philos[i]) != 0)
		{
			/*error stuff here return and destroy mlx*/
			return (0);
		}
		i++;
	}
	return (1);
}

static	int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
		{
			/*error stuff here if joining fails*/
			return (0);
		}
		i++;
	}
	return (1);
}

void	table_is_ready(t_data *data)
{
	int			i;
	pthread_t	moni;

	i = 0;
	if (data->nbr_of_meals == 0 && data->nbr_of_meals)
		return ;
	if (!create_thread(data))
		return ;
	if (pthread_create(&moni, NULL, &monitor, data) != 0)
	{
		// destroy all;
	}
	data->start = get_current_time();
	pthread_mutex_lock(&data->philos->philo_mutex);
	data->threads_ready = true;
	pthread_mutex_unlock(&data->philos->philo_mutex);
	if (!join_threads(data))
		return ;
	if (data->nbr_of_meals == data->philos[0].meal_counter)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->full = 1;
		pthread_mutex_unlock(&data->data_mutex);
	}
	pthread_join(moni, NULL);
}