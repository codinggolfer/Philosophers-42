/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:47:33 by eagbomei          #+#    #+#             */
/*   Updated: 2024/03/22 16:18:35 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
pthread_mutex_t lock;

void	*read_balance(void *balance)
{
	pthread_mutex_lock(&lock);
	printf("argument recieved here: ");
	printf("%i\n", *(int*)balance);
	int *bal = malloc(sizeof(int));
	*bal = *(int*) balance;
	int i = 1;

	while (i <= 10)
	{
		*bal += 100;
		printf("100 added to the balance, balance now: %i\n", *bal);
		i++;
	}
	pthread_mutex_unlock(&lock);
	pthread_exit(bal);
}


int main(void)
{
	int balance = 0;
	int balance1 = 0; 
	pthread_t bal;
	pthread_t bal2;
	int *new_bal;

	printf("balance at begining: %d\n", balance);
	pthread_create(&bal, NULL, &read_balance, &balance);
	pthread_create(&bal2, NULL, &read_balance, &balance1);

	pthread_join(bal, (void *)&new_bal);
	pthread_join(bal, (void *)&new_bal);
	printf("balance at the end: %d\n", *new_bal);
}

