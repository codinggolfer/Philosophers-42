/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:31:35 by eagbomei          #+#    #+#             */
/*   Updated: 2024/03/28 11:08:18 by eagbomei         ###   ########.fr       */
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

typedef pthread_mutex_t	t_mtx;


/* carries the input */
typedef struct s_data
{
	int		dead;
	int 	nbr_of_philos;
	long	time_to_die;
	long	sleep;
	int 	nbr_of_meals;
	long	start;
	long	eat;
	t_fork	*forks;
	t_philo	*philos;
	
}	t_data;
/*has the forks*/
typedef struct s_fork
{
	t_mtx	*fork;
	int		fork_id;
}	t_fork;
/*for threading and philoshit*/
typedef struct s_philo
{
	t_data		*philo;
	int			id;
	id_t		i;
	long		last_meal_time; //time from last meal
	t_fork		*left_fork;
	t_fork		*left_fork;
	pthread_t	thread_id; //philosopher is a thread
	int			meal_counter;
}	t_philo;

//----------utils-----------
long	ft_atol(const char *str);
int		check_digit(char *str);
void	data_init(t_data *philo);

#endif