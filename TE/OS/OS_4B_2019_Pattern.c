//Aanchal Sarda
//TE IT 9057
//ASSIGNMENT 4-B
//Problem Statement :  Thread synchronization and mutual exclusion using mutex. Application to demonstrate: Reader-Writer problem with reader priority.

#include <stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

pthread_mutex_t wlock, rlock;
int data = 0, rcount = 0;

void *write(void *arg)
{
	int waiting;

	waiting = rand()%3;
	printf("\nWriter is trying to enter critical section");
	pthread_mutex_lock(&wlock);
	data++;
	printf("\nWriter has entered critical section");
	//sleep(waiting);
	pthread_mutex_unlock(&wlock);
	printf("\nWriter has left critical section");
	//sleep(5);
}
void *read(void *arg)
{
	int waiting;

	waiting = rand()%3;
	printf("\nReader is trying to enter critical section");
	pthread_mutex_lock(&rlock);
	rcount++;

	if(rcount == 1)
	pthread_mutex_lock(&wlock);

	pthread_mutex_unlock(&rlock);
	printf("\nReader %d has entered the critical section",rcount);
	printf("\nReader is reading data :%d",data);
	//sleep(waiting);
	pthread_mutex_lock(&rlock);
	rcount--;
	if(rcount == 0)
	pthread_mutex_unlock(&wlock);

	pthread_mutex_unlock(&rlock);
	printf("\nReader has left critical section");
}

void main()
{
	int i;

	pthread_mutex_init(&wlock,NULL);
	pthread_mutex_init(&rlock,NULL);

	pthread_t reader[5], writer[5];

	for(i=0; i<3; i++)
	{
		pthread_create(&reader[i],NULL,read,NULL);
		pthread_create(&writer[i],NULL,write,NULL);
	}
	for(i=0; i<3; i++)
	{
		pthread_join(reader[i],NULL);
		pthread_join(writer[i],NULL);
		
	}

}
