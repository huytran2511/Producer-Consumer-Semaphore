CC=gcc
CCFLAGS=-std=c11 -g

mizzo : belt.o producer.o consumer.o mizzo.o
	$(CC) $(CCFLAGS) -o mizzo $^ -lpthread -lrt

belt.o : belt.h belt.c

producer.o: producer.h producer.c

consumer.o: consumer.h consumer.c

mizzo.o : mizzo.c

clean :
	rm -fr mizzo $(OBJS) *.o