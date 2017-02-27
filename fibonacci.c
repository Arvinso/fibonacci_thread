/*
 * main.c
 *
 *  Created on: Feb 25, 2017
 *      Author: arvin
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sysexits.h>

long long *fibptr;

void* fibonacci_process(void* arg)
{
	long long *limitptr = (long long*) arg;
	long long limit = *limitptr;

	fibptr = malloc(++limit * sizeof(*fibptr));  //memory allocated using malloc

	long long first = 0, second = 1, next = 0;
	for(long long i = 0; i < limit; i++)
	{
		  if ( i <= 1 )
			 next = i;
		  else
		  {
			 next = first + second;
			 first = second;
			 second = next;
		  }

		fibptr[i] = next;
	}

	pthread_exit(0);
}

int main(int argc, char **argv )
{
	if(argc < 2)
	{
		printf("Usage: %s <num>\n", argv[0]);
		exit(EX_USAGE);
	}

	long long *limit = malloc(sizeof(*limit));
	*limit = atoll(argv[1]);

	//Thread ID;
	pthread_t tid;

	//Create attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, fibonacci_process, limit);

	//wait until thread is done with work

	pthread_join(tid, NULL);

	printf("-------------\n");

	for(long long i = 0; i <= *limit; i++)
	{
		printf("fibonacci for limit %i is %lld\n", i, fibptr[i]);
	}

	free(fibptr);
	free(limit);

	return EXIT_SUCCESS;
}

