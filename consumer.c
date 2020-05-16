/**********************
***********************
Student 1: Huy Tran
Red ID: 818608122

Student 2: Hosun Yoo
Red ID: 819543212

CS-570
a05
consumer.c
***********************
***********************/

#include "consumer.h"

/* function to initialize the Consumer Data Structures to be passed to threads */
CONSUMER* createConsumer(BUFFER* buffer) {
	CONSUMER* consumer = calloc(1, sizeof(CONSUMER));
	consumer->belt = buffer;
	consumer->totFrogs = consumer->totEscargots = consumer->totConsumed = 0;

	return consumer;
}

/* function to simulate time required to consume a candy */
void consume(long time) {
	struct timespec SleepTime;
	SleepTime.tv_sec = time / 1000;
	SleepTime.tv_nsec = (time % 1000) * 1000000;
	nanosleep(&SleepTime, NULL);
}

/* function for consumer threads */
void* consumer(void* arg) {
	CONSUMER* consumer = (CONSUMER*)arg;
	BUFFER* belt = consumer->belt;

	while (belt->consumedCandy < TOTALCANDIES) {
		sem_wait(&unconsumed);
		sem_wait(&mutex);

		//remove item from buffer
		int candy = removeCandy(belt);

		if (candy == FROG) { // if removed frog
			++consumer->totFrogs;
			int i = --belt->frogsOnBelt;
			int j = belt->escargotsOnBelt;
			int k = belt->onBelt;
			int l = belt->producedCandy;

			if (pthread_equal(belt->lucy_id, pthread_self())) { // if this is lucy thread
				printf("\nBelt: %d frogs + %d escargots = %d. produced: %d\tLucy consumed crunchy frog bite.\n", i, j, k, l);
			}
			else { // if this is ethel thread
				printf("\nBelt: %d frogs + %d escargots = %d. produced: %d\tEthel consumed crunchy frog bite.\n", i, j, k, l);
			}

			sem_post(&frog_empty); // increment frog_empty semaphore by 1
		}
		else { // if removed escargot
			++consumer->totEscargots;
			int i = belt->frogsOnBelt;
			int j = --belt->escargotsOnBelt;
			int k = belt->onBelt;
			int l = belt->producedCandy;
			if (pthread_equal(belt->lucy_id, pthread_self())) {
				printf("\nBelt: %d frogs + %d escargots = %d. produced: %d\tLucy consumed escargot sucker.\n", i, j, k, l);
			}
			else {
				printf("\nBelt: %d frogs + %d escargots = %d. produced: %d\tEthel consumed escargot sucker.\n", i, j, k, l);
			}
		}

		sem_post(&mutex);
		sem_post(&emptyslots);

		//consume item
		if (pthread_equal(belt->lucy_id, pthread_self())) {
			consume(belt->time_L);
		}
		else {
			consume(belt->time_E);
		}
	}
	sem_post(&barrier);
}