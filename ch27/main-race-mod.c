#include <stdio.h>

#include "common_threads.h"

int balance = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    // lock worker thread access
    Pthread_mutex_lock(&lock);
    balance++; // unprotected access
    Pthread_mutex_unlock(&lock);
 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    
    // lock main threads access
    Pthread_mutex_lock(&lock);
    balance++;
    Pthread_mutex_unlock(&lock); 
    
    Pthread_join(p, NULL);
    return 0;
}
