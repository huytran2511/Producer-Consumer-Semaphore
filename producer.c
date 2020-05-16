#include "producer.h"

/* function to simulate time required to produce a candy */
void produce(long time) {
    struct timespec SleepTime;
    SleepTime.tv_sec = time / 1000; // # secs
    SleepTime.tv_nsec = (time % 1000) * 1000000; // # nanosecs
    nanosleep(&SleepTime, NULL);
}

/* function for frog producer thread */
void* frogProducer(void* buffer) {
    BUFFER* belt = (BUFFER*)buffer;

    while (belt->producedCandy < TOTALCANDIES) {
        sem_wait(&emptyslots);
        sem_wait(&mutex);

        //insert candy onto belt
        insertCandy(belt, FROG);
        ++belt->frogsProduced;
        int i = ++belt->frogsOnBelt;
        int j = belt->escargotsOnBelt;
        int k = belt->onBelt;
        int l = belt->producedCandy;
        printf("\nBelt: %d frogs + %d escargots = %d. produced: %d\tAdded crunchy frog bite.\n", i, j, k, l);

        sem_post(&mutex);
        sem_post(&unconsumed);
        sem_wait(&frog_empty); // decrement frog_empty semaphore by 1

        //produce candy
        produce(belt->time_f);
    }
    sem_post(&barrier);
}

/* function for escargot producer thread */
void* escargotProducer(void* buffer) {
    BUFFER* belt = (BUFFER*)buffer;

    while (belt->producedCandy < TOTALCANDIES) {
        sem_wait(&emptyslots);
        sem_wait(&mutex);

        //insert candy onto belt
        insertCandy(belt, ESCARGOT);
        ++belt->escargotsProduced;
        int i = belt->frogsOnBelt;
        int j = ++belt->escargotsOnBelt;
        int k = belt->onBelt;
        int l = belt->producedCandy;
        printf("\nBelt: %d frogs + %d escargots = %d. produced: %d\tAdded escargot sucker.\n", i, j, k, l);

        sem_post(&mutex);
        sem_post(&unconsumed);

        //produce candy
        produce(belt->time_e);
    }
    sem_post(&barrier);
}
