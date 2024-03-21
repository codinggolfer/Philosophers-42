/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:31:35 by eagbomei          #+#    #+#             */
/*   Updated: 2024/03/21 16:47:42 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define PHILO_MAX 200

typedef struct s_data
{
	int	dead;
}	t_data;

typedef struct s_philo
{
	t_data	*philo;
	int		value;
}	t_philo;

//----------utils-----------
int	ft_atoi(char *str);
int	check_digit(char *str);

#endif