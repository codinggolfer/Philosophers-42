/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:43:03 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/17 16:45:07 by eagbomei         ###   ########.fr       */
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
	// if (number * mp > 2147483647 || number * mp < -2147483648)
	// 	ft_error("Error");
	// if (number == 0 && mp == -1)
	// 	ft_error("Error");
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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	wait_all(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->philos->philo_mutex);
		if (data->threads_ready == true)
		{
			pthread_mutex_unlock(&data->philos->philo_mutex);
			break ;
		}
	}
	pthread_mutex_lock(&data->philos->philo_mutex);
	data->philos->philo_threads++;
	pthread_mutex_unlock(&data->philos->philo_mutex);
}
