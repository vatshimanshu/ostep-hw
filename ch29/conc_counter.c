#include<stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "common_threads.h"

typedef struct __counter_t
{
    int value;
    pthread_mutex_t lock;

} counter_t;

void init(counter_t *c)
{
    c->value = 0;
    Pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    c->value++;
    Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    c->value--;
    Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    int rc = c->value;
    Pthread_mutex_unlock(&c->lock);
    return rc;
}

counter_t counter;

void *inc(void *arg)
{
    int i;

    for (i = 0; i < 1000000; i++)
    {
        increment(&counter);
    }
    return NULL;
}

int main() {
    pthread_t p[4];
    init(&counter);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    Pthread_create(&p[0], NULL, inc, NULL);
    Pthread_create(&p[1], NULL, inc, NULL);
    Pthread_create(&p[2], NULL, inc, NULL);
    //Pthread_create(&p[3], NULL, inc, NULL);
    Pthread_join(p[0], NULL);
    Pthread_join(p[1], NULL);
    Pthread_join(p[2], NULL);
    //Pthread_join(p[3], NULL);

    gettimeofday(&end, NULL);
    assert(get(&counter) == 3000000);

    printf("Time taken for the update is : %ld micro seconds\n",
           ((end.tv_sec * 1000000 + end.tv_usec) -
            (start.tv_sec * 1000000 + start.tv_usec)));
    return 0;
}