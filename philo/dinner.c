/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:40:25 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/22 17:17:30 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_thread(t_data *data, pthread_t moni)
{
	int			i;

	i = -1;
	while (++i < data->nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &main_routine,
				&data->philos[i]) != 0)
		{
			while (--i > 0)
				pthread_join(data->philos[i].thread_id, NULL);
			printf("pthread_create Error");
			return (0);
		}
	}
	if (pthread_create(&moni, NULL, &monitor, data) != 0)
	{
		printf("pthread_create Error for monitor");
		join_threads(data);
		return (0);
	}
	return (1);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
		{
			printf("Error while joining threads");
			return (0);
		}
		i++;
	}
	return (1);
}

void	table_is_ready(t_data *data)
{
	pthread_t	moni;

	moni = NULL;
	if (data->nbr_of_meals == 0)
		return ;
	if (data->nbr_of_philos == 1)
	{
		lone_philo(data->philos);
		return ;
	}
	if (!create_thread(data, moni))
		return ;
	data->start = get_exact_time();
	locker(&data->philos->philo_mutex);
	data->threads_ready = true;
	unlocker(&data->philos->philo_mutex);
	if (!join_threads(data))
		return ;
	if (data->nbr_of_meals == data->philos[0].meal_counter)
		set_value(&data->data_mutex, &data->full, 1);
	pthread_join(moni, NULL);
}