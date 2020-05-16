/**********************
***********************
Student 1: Huy Tran
Red ID: 818608122

Student 2: Hosun Yoo
Red ID: 819543212

CS-570
a05
mizzo.c
***********************
***********************/

#include "belt.h"
#include "producer.h"
#include "consumer.h"

#define BADFLAG -1

int main(int argc, char** argv) {

	int option;
	long time_E = 0, time_L = 0, time_f = 0, time_e = 0;

	while ((option = getopt(argc, argv, "E:L:f:e:")) != -1) {
		switch (option) {
		case 'E':
			time_E = atoi(optarg);
			break;
		case 'L':
			time_L = atoi(optarg);
			break;
		case 'f':
			time_f = atoi(optarg);
			break;
		case 'e':
			time_e = atoi(optarg);
			break;
		default:
			exit(BADFLAG);
		}
	}

	BUFFER* buffer = createBelt(BUFFSIZE);

	buffer->time_f = time_f;
	buffer->time_e = time_e;
	buffer->time_L = time_L;
	buffer->time_E = time_E;

	CONSUMER* Lucy = createConsumer(buffer);
	CONSUMER* Ethel = createConsumer(buffer);

	sem_init(&mutex, 0, 1); // block the critical section
	sem_init(&unconsumed, 0, 0); // make sure belt has items before consuming
	sem_init(&emptyslots, 0, BUFFSIZE); // make sure belt has space before producing
	sem_init(&frog_empty, 0, 2); // make sure only max 3 frogs are on belt at all times
	sem_init(&barrier, 0, 0);

	pthread_t frogs, escargots, lucy, ethel;

	pthread_create(&frogs, NULL, frogProducer, (void*)buffer);
	pthread_create(&escargots, NULL, escargotProducer, (void*)buffer);
	pthread_create(&lucy, NULL, consumer, (void*)Lucy);
	pthread_create(&ethel, NULL, consumer, (void*)Ethel);

	buffer->lucy_id = lucy;
	buffer->ethel_id = ethel;

	// block process until Belt functions are complete
	sem_wait(&barrier);
	sem_wait(&barrier);
	sem_wait(&barrier);

	printf("\n\n\nPRODUCTION REPORT\n");
	printf("\n----------------------------------------\n");
	printf("\ncrunchy frog bite producer generated %d candies\n", buffer->frogsProduced);
	printf("\nescargot sucker producer generated %d candies\n", buffer->escargotsProduced);
	printf("\nLucy consumed %d crunchy frogs bites + %d escargot suckers = %d \n", Lucy->totFrogs, Lucy->totEscargots, Lucy->totFrogs + Lucy->totEscargots);
	printf("\nEthel consumed %d crunchy frogs bites + %d escargot suckers = %d \n\n", Ethel->totFrogs, Ethel->totEscargots,	Ethel->totFrogs + Ethel->totEscargots);

	sem_destroy(&mutex);
	sem_destroy(&unconsumed);
	sem_destroy(&emptyslots);
	sem_destroy(&barrier);
	sem_destroy(&frog_empty);
	
	return 0;
}