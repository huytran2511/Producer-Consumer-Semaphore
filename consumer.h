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
