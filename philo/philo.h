/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:31:35 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/18 16:45:58 by eagbomei         ###   ########.fr       */
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
/*philo threads are in sync*/
typedef enum e_philos_ready
{
	true,
	false,
}	t_philos_ready;

/*philo status*/
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKE_F_FORK,
	TAKE_S_FORK,
}	t_status;

/*has the forks*/
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

/*for threading and philoshit*/
typedef struct s_philo
{
	int			id;
	id_t		i;
	long		last_meal_time; //time from last meal
	t_fork		*first_fork; //right fork
	t_fork		*second_fork; //left fork
	pthread_t	thread_id; //philosopher is a thread
	t_mtx		philo_mutex; // helper for race conditions
	int			meal_counter;
	int			philo_threads;	
	t_data		*data;
	t_mtx		*meal_lock;
}	t_philo;

/* carries the input */
struct s_data
{
	int				dead;
	int				nbr_of_philos;
	long			time_to_die;
	size_t			sleep;
	int				nbr_of_meals;
	long			start;
	long			eat;
	int				full;
	t_philos_ready	threads_ready;
	t_mtx			data_mutex;
	t_mtx			print_mutex;
	t_mtx			time_mutex;
	t_fork			*forks;
	t_philo			*philos;

};

//----------utils-----------
long	ft_atol(const char *str);
int		check_digit(char *str);
void	data_init(t_data *philo);
void	wait_all(t_data *data);
void	print_status(t_status status, t_philo *philo);


/*-----Usleep handmade*------*/
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

/*----routine-----*/
void	*main_routine(void *arg);


/*----THREAD-------*/
void	table_is_ready(t_data *data);

/*----monitor-----*/
void	*monitor(void *arg);
int		sim_finished(t_data *moni);

#endif