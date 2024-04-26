/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:43:03 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/26 14:33:34 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long		mp;
	long		number;

	mp = 1;
	number = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			mp *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str++ - '0';
	}
	return (number * mp);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

size_t	get_exact_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_exact_time();
	while ((get_exact_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	wait_all(t_data *data)
{
	while (1)
	{
		locker(&data->philo_mutex);
		if (data->threads_ready == true)
		{
			unlocker(&data->philo_mutex);
			break ;
		}
		unlocker(&data->philo_mutex);
	}
	locker(&data->philo_mutex);
	data->philos->philo_threads++;
	unlocker(&data->philo_mutex);
}

