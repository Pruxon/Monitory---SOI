#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include "monitor.h"
#include "Buffer.cpp"

#define CONSNUMBER 5

using namespace std;

Buffer buffer[CONSNUMBER];

void *producer(void *)
{
    while(true)
    {
        usleep(rand()%500000);
        int where = rand()%5;
        if (buffer[where].isFull())
        {
            where = where+1%5;
            buffer[where].pruduce(where);
        }
        else
        {
            buffer[where].pruduce(where);
        }
    }
}

void *consumer(void *number)
{
    while (true)
    {
        usleep(rand()%(3000000*((long)number+1)));
        buffer[(long)number].consume((long)number);
    }
}

int main()
{
    pthread_t prod, cons[CONSNUMBER];

    srand((unsigned) time(NULL));

    pthread_create(&prod, NULL, producer, NULL);
    for (long i = 0; i < CONSNUMBER; i++)
        pthread_create(&cons[i], NULL, consumer, (void *)i);

    pthread_join(prod, NULL);

    for (int i = 0; i < CONSNUMBER; i++)
        pthread_join(cons[i], NULL);

    return 0;
}
