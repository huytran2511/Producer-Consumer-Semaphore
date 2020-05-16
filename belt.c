#include "belt.h"

/* function to initialize belt to be referenced by threads */
BUFFER* createBelt(unsigned int capacity) {
	BUFFER* belt = calloc(1, sizeof(BUFFER));
	belt->array = calloc(capacity, sizeof(int));
	belt->front = belt->onBelt = 0;
	belt->capacity = capacity;
	belt->rear = capacity - 1;
	belt->frogsOnBelt = belt->escargotsOnBelt = 0;
	belt->producedCandy = belt->consumedCandy = 0;
	belt->time_f = belt->time_e = belt->time_L = belt->time_E = 0;

	return belt;
}

/* function to insert candy onto belt FIFO */
void insertCandy(BUFFER* buffer, int item) {
	buffer->rear = (buffer->rear + 1) % buffer->capacity;
	buffer->array[buffer->rear] = item;
	++buffer->onBelt;
	++buffer->producedCandy;
}

/* function to remove candy from belt and return candy type FIFO */
int removeCandy(BUFFER* buffer) {
	int item = buffer->array[buffer->front];
	buffer->front = (buffer->front + 1) % buffer->capacity;
	--buffer->onBelt;
	++buffer->consumedCandy;

	return item;
}
