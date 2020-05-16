#ifndef _PRODUCER_H_
#define _PRODUCER_H_

#include "belt.h"

void produce(long time);
void* frogProducer(void* buffer);
void* escargotProducer(void* buffer);

#endif
