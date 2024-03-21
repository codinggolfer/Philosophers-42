/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:47:33 by eagbomei          #+#    #+#             */
/*   Updated: 2024/03/21 17:00:24 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
pthread_mutex_t lock;

void	*read_balance(void *balance)
{
	t_philo *bal = (t_philo *) balance;
	pthread_mutex_lock(&lock);
	
	int i = 1;
	while (i < 100)
	{
		bal->value += i;
		printf("%i\n", bal->value);
		i++;
	}
	pthread_mutex_unlock(&lock);
	return (NULL);
}


int main(void)
{
	int balance = 0;
	pthread_t bal;
	t_philo	value;

	value.value = 0;
	pthread_create(&bal, NULL, &read_balance, (void *)&value);
	pthread_create(&bal, NULL, &read_balance, (void *)&value);

	pthread_join(bal, NULL);
	pthread_join(bal, NULL);
	printf("%d", value.value);
}

