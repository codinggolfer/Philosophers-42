/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:29:03 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/18 16:46:24 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (i < philo->nbr_of_philos)
	{
		filo = philo->philos + i;
		filo->id = i + 1;
		filo->meal_counter = 0;
		filo->philo_threads = 0;
		pthread_mutex_init(&filo->philo_mutex, NULL);
		filo->data = philo;
		init_forks(filo, philo->forks, i);
		i++;
	}
}

void	data_init(t_data *philo)
{
	int	i;

	i = 0;
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
	philo->full = 0;
	philo->threads_ready = false;
	while (i < philo->nbr_of_philos)
	{
		if (pthread_mutex_init(&philo->forks[i].fork, NULL) != 0)
			return ;
		philo->forks[i].fork_id = i;
		i++;
	}
	if (pthread_mutex_init(&philo->data_mutex, NULL) != 0)
		return ;
	if (pthread_mutex_init(&philo->print_mutex, NULL) != 0)
		return ;
	if (pthread_mutex_init(&philo->time_mutex, NULL) != 0)
		return ;
	init_philos(philo->philos, philo);
}