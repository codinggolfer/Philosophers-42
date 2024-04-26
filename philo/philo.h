/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:31:35 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/26 15:04:47 by eagbomei         ###   ########.fr       */
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

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef enum e_philos_ready
{
	true,
	false,
}	t_philos_ready;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKE_F_FORK,
	TAKE_S_FORK,
}	t_status;

typedef struct s_fork
{
	t_mtx	fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	int			meal_counter;
	int			philo_threads;	
	t_data		*data;
}	t_philo;

struct s_data
{
	long			dead;
	int				fail;
	int				detach;
	int				nbr_of_philos;
	long			time_to_die;
	size_t			sleep;
	int				nbr_of_meals;
	long			start;
	long			eat;
	long			full;
	t_philos_ready	threads_ready;
	t_mtx			philo_mutex;
	t_mtx			data_mutex;
	t_mtx			print_mutex;
	t_mtx			time_mutex;
	t_fork			*forks;
	t_philo			*philos;

};

long	ft_atol(const char *str);
int		check_digit(char *str);
void	data_init(t_data *philo);
void	wait_all(t_data *data);
void	print_status(t_status status, t_philo *philo);
size_t	get_exact_time(void);
int		ft_usleep(size_t milliseconds);
void	*main_routine(void *arg);
void	table_is_ready(t_data *data);
int		join_threads(t_data *data);
void	*monitor(void *arg);
int		sim_finished(t_data *moni);
void	lone_philo(t_philo *philo);
void	set_value(t_mtx *mutex, long *value, long time);
void	locker(t_mtx *mutex);
void	unlocker(t_mtx *mutex);
int		check_available(t_mtx *mutex, long value);
void	free_all(t_data *data);

#endif