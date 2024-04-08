/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:40:25 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/08 17:53:19 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_is_ready(t_data *data)
{
	int	i;

	i = 0;
	if (data->nbr_of_meals == 0)
		return ;
	while (i++ < data->nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &main_routine,
				&data->philos[i]) != 0)
		{
			/*error stuff here return and destroy mlx*/
		}
	}
	data->start = get_current_time();
	data->threads_ready = true;
	i = 0;
	while (i++ < data->philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
		{
			/*error stuff here if joining fails*/
		}
	}
}