/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:29:03 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/08 17:40:15 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_philo *filo, t_data *forks, int philo_pos)
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

static void	init_philos(t_data *philo)
{
	int		i;
	t_philo	*filo;

	i = 0;
	while (i++ < philo->nbr_of_philos)
	{
		filo = philo->philos + i;
		filo->id = i + 1;
		filo->meal_counter = 0;
		philo->philos = philo;
		init_forks(filo, philo->forks, i);
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
	philo->threads_ready = false;
	while (i++ < philo->nbr_of_philos)
	{
		pthread_mutex_init(&philo->forks[i].fork, NULL);
		philo->forks[i].fork_id = i; //for dbugging.
	}
	init_philos(philo);
}