/**********************
***********************
Student 1: Huy Tran
Red ID: 818608122

Student 2: Hosun Yoo
Red ID: 819543212

CS-570
a05
consumer.h
***********************
***********************/

#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#include "belt.h"

typedef struct {
	BUFFER* belt;
	int totFrogs, totEscargots, totConsumed;
} CONSUMER;

CONSUMER* createConsumer(BUFFER* buffer);
void consume(long time);
void* consumer(void* arg);

#endif