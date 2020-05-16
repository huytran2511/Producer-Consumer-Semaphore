/**********************
***********************
Student 1: Huy Tran
Red ID: 818608122

Student 2: Hosun Yoo
Red ID: 819543212

CS-570
a05
producer.h
***********************
***********************/

#ifndef _PRODUCER_H_
#define _PRODUCER_H_

#include "belt.h"

void produce(long time);
void* frogProducer(void* buffer);
void* escargotProducer(void* buffer);

#endif