#ifndef _BELT_H_
#define _BELT_H_

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFSIZE 10
#define TOTALCANDIES 100
#define FROG 1
#define ESCARGOT 2

/* define semaphores to be used */
sem_t mutex, barrier;
sem_t unconsumed, emptyslots;
sem_t frog_empty;

/* struct to represent a FIFO belt */
typedef struct {
	int* array;
	int front, rear;
	unsigned int capacity;
	int onBelt; // total candies on belt
	int frogsOnBelt, escargotsOnBelt; // total frogs and escargots on belt
	int frogsProduced, escargotsProduced; // total frogs and escargots produced
	int producedCandy, consumedCandy; // total candies produced and consumed
	long time_f, time_e, time_L, time_E; // sleep time for each thread
	pthread_t lucy_id, ethel_id; // thread id 
} BUFFER;
 
BUFFER* createBelt(unsigned int capacity);
void insertCandy(BUFFER* buffer, int item);
int removeCandy(BUFFER* buffer);

#endif
