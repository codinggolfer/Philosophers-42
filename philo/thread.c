/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:47:33 by eagbomei          #+#    #+#             */
/*   Updated: 2024/04/04 18:25:37 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
// pthread_mutex_t lock;

// void	*read_balance(void *balance)
// {
// 	pthread_mutex_lock(&lock);
// 	printf("argument recieved here: ");
// 	printf("%i\n", *(int*)balance);
// 	int *bal = malloc(sizeof(int));
// 	*bal = *(int*) balance;
// 	int i = 1;

// 	while (i <= 10)
// 	{
// 		*bal += 100;
// 		printf("100 added to the balance, balance now: %i\n", *bal);
// 		i++;
// 	}
// 	pthread_mutex_unlock(&lock);
// 	pthread_exit(bal);
// }

pthread_mutex_t mutex;
int mails = 0;

void *routine()
{
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 100000000; i++)
		mails++;
	pthread_mutex_unlock(&mutex);
	return(NULL);
}
// void *routine2()
// {
// 	sleep(2);
// 	printf("theards2 value for x: %d\n", x);
// 	return(NULL);
// }

int main(void)
{
	pthread_t t1[8];
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 8; i++)
	{
		if (pthread_create(&t1[i], NULL, &routine, NULL) != 0)
		{
			printf("error1");
			exit(1);
		}
		printf("thread process %d has started exec\n", i);
	}
	for (int i = 0; i < 8; i++)
	{
		if (pthread_join(t1[i], NULL) != 0)
		{
			printf("error3");
			exit(1);
		}
		printf("thread process %d has stopped exec\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("number of mails in mailbox: %d\n", mails);
}

