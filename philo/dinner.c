/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:40:25 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/16 16:53:20 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_is_ready(t_data *data)
{
	int	i;
	pthread_t moni;

	i = 0;
	if (data->nbr_of_meals == 0 && data->nbr_of_meals)
		return ;
	if (pthread_create(&moni, NULL, &monitor, data) != 0)
	{
		// destroy all;
	}
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &main_routine,
				&data->philos[i]) != 0)
		{
			/*error stuff here return and destroy mlx*/
		}
		i++;
	}
	data->start = get_current_time();
	data->threads_ready = true;
	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
		{
			/*error stuff here if joining fails*/
		}
		i++;
	}
	if (data->nbr_of_meals == data->philos->meal_counter)
		data->full = 1;
	pthread_join(moni, NULL);
}