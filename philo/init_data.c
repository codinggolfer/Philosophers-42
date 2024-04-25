/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:29:03 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/25 13:48:11 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_init(t_data *philo)
{
	free (philo->forks);
	free (philo->philos);
}

static void	init_forks(t_philo *filo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = filo->data->nbr_of_philos;
	filo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	filo->second_fork = &forks[philo_pos];
	if (filo->id % 2 == 0)
	{
		filo->first_fork = &forks[philo_pos];
		filo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
}

static void	init_philos(t_philo *filo, t_data *philo)
{
	int	i;

	i = 0;
	philo->full = 0;
	philo->threads_ready = false;
	philo->detach = 0;
	while (i < philo->nbr_of_philos)
	{
		filo = philo->philos + i;
		filo->id = i + 1;
		filo->meal_counter = 0;
		filo->philo_threads = 0;
		filo->data = philo;
		if (pthread_mutex_init(&filo->philo_mutex, NULL) != 0)
		{
			return ;
		}
		init_forks(filo, philo->forks, i);
		i++;
	}
	if (pthread_mutex_init(&philo->data_mutex, NULL) != 0 || \
		pthread_mutex_init(&philo->print_mutex, NULL) != 0 || \
		pthread_mutex_init(&philo->time_mutex, NULL) != 0)
		free_init(philo);
}

void	data_init(t_data *philo)
{
	int	i;

	i = -1;
	philo->philos = malloc(sizeof(t_philo) * philo->nbr_of_philos);
	if (!philo->philos)
	{
		printf("malloc error\n");
		return ;
	}
	philo->forks = malloc(sizeof(t_fork) * philo->nbr_of_philos);
	if (!philo->forks)
	{
		printf("malloc error\n");
		return ;
	}
	while (++i < philo->nbr_of_philos)
	{
		if (pthread_mutex_init(&philo->forks[i].fork, NULL) != 0)
		{
			free (philo->forks);
			free (philo->philos);
			return ;
		}
	}
	init_philos(philo->philos, philo);
}
