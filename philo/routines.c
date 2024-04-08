/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:09:21 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/08 17:58:46 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*main_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all(philo->data);
	while (1)
	{
		if (philo->data->nbr_of_meals == 0)
			break ;
		//eat function
		eating(philo);
		//sleeping function
		sleeping()
	}
	return (NULL);
}