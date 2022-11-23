#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "common_threads.h"

#define NUMCPUS 4
#define THRESHOLD 4

typedef struct __counter_t
{
    int global;                     // global count
    pthread_mutex_t glock;          // global lock
    int local[NUMCPUS];             // per-CPU count
    pthread_mutex_t llock[NUMCPUS]; // ... and locks
    int threshold;                  // update frequency
} counter_t;

// init: record threshold, init locks, init values
// of all local counts and global count
void init(counter_t *c, int threshold)
{
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++)
    {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

// update: usually, just grab local lock and update
// local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void update(counter_t *c, int threadID, int amt)
{
    int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold)
    {
        // transfer to global (assumes amt>0)
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
}

// get: just return global amount (approximate)
int get(counter_t *c)
{
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);
    return val; // only approximate!
}

counter_t counter;

void *inc(int id)
{
    int i;

    pthread_t threadID = pthread_self();
    for (i = 0; i < 1000000; i++)
    {
        update(&counter, (int)threadID, 1);
    }
    return NULL;
}

int main()
{
    pthread_t p[4];
    //cpu_set_t cpuset;
    init(&counter, THRESHOLD);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    Pthread_create(&p[0], NULL, inc, 0);
    /*CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(p[0],
                           sizeof(cpu_set_t), &cpuset);
*/
    Pthread_create(&p[1], NULL, inc, 1);
/*    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(p[1],
                           sizeof(cpu_set_t), &cpuset);
*/
    Pthread_create(&p[2], NULL, inc, 2);
/*    CPU_ZERO(&cpuset);
    CPU_SET(2, &cpuset);
    pthread_setaffinity_np(p[2],
                           sizeof(cpu_set_t), &cpuset);
*/
    Pthread_create(&p[3], NULL, inc, 3);
/*    CPU_ZERO(&cpuset);
    CPU_SET(3, &cpuset);
    pthread_setaffinity_np(p[3],
                           sizeof(cpu_set_t), &cpuset);
*/
    Pthread_join(p[0], NULL);
    Pthread_join(p[1], NULL);
    Pthread_join(p[2], NULL);
    Pthread_join(p[3], NULL);

    gettimeofday(&end, NULL);

    printf("Time taken for the update is : %ld micro seconds\n",
           ((end.tv_sec * 1000000 + end.tv_usec) -
            (start.tv_sec * 1000000 + start.tv_usec)));
    return 0;
}