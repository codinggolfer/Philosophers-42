/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:29:03 by eagbomei          #+#    #+#             */
/*   Updated: 2024/03/28 11:13:16 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_data *philo)
{
	int		i;
	t_philo *filo;

	i = 0;
	while (i < philo->nbr_of_philos)
	{
		filo = philo->philos + i;
		filo->id = i + 1;
		filo->meal_counter = 0;
		philo->philos = philo;
		init_forks(filo, philo->forks, i); // TODO &  i is the position in the table
	}
}

void	data_init(t_data *philo)
{
	int	i;

	i = 0;
	philo->philos = malloc(philo->nbr_of_philos);
	if (!philo->philos)
		printf("malloc error\n");
	philo->forks = malloc(philo->nbr_of_meals);
	if (!philo->forks)
		printf("malloc error\n");
	//need to return if one of the mallocs fails

	while (i < philo->nbr_of_philos)
	{
		pthread_mutex_init(philo->forks[i].fork, NULL);
		philo->forks[i].fork_id = i; //for dbugging.
		i++;
	}
	init_philos(philo);
}