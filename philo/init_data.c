/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:29:03 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/26 14:37:00 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_init(t_data *data)
{
	data->fail = 1;
	free (data->forks);
	free (data->philos);
}

static void	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->fail = 0;
	while (++i < data->nbr_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
		{
			while (--i)
				pthread_mutex_destroy(&data->forks[i].fork);
			free_init(data);
			return ;
		}
	}
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		free_init(data);
	if (data->fail == 1 || pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return ;
	if (data->fail == 1 || pthread_mutex_init(&data->time_mutex, NULL) != 0)
		return ;
	if (data->fail == 1 || pthread_mutex_init(&data->philo_mutex, NULL) != 0)
		return ;
}

static void	init_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->data->nbr_of_philos;
	philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
}

static void	init_philos(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->full = 0;
	data->threads_ready = false;
	while (i < data->nbr_of_philos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->meal_counter = 0;
		philo->philo_threads = 0;
		philo->data = data;
		init_forks(philo, data->forks, i);
		i++;
	}
}

void	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
	{
		printf("malloc error\n");
		return ;
	}
	data->forks = malloc(sizeof(t_fork) * data->nbr_of_philos);
	if (!data->forks)
	{
		printf("malloc error\n");
		return ;
	}
	while (++i < data->nbr_of_philos)
	// {
	// 	if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
	// 	{
	// 		free (data->forks);
	// 		free (data->philos);
	// 		return ;
	// 	}
	// }
	init_mutex(data);
	init_philos(data->philos, data);
}
