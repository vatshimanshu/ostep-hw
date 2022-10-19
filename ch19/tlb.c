#define _GNU_SOURCE
#include <sched.h>
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define PAGESIZE 16384

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("This program expects two argument. Please"
               " specify the number of pages and number of trials" 
               "to access\n");
        return 0;
    }

    struct timeval start, end;

    int num_pages = atoi(argv[1]);
    int num_trials = atoi(argv[2]);
    int loop = num_trials;

    /* cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &set);
    */

    int jump = PAGESIZE / sizeof(int);
    int *arr = calloc(9000000, sizeof(int));

    gettimeofday(&start, NULL);
    while (loop > 0)
    {
        for (int i = 0; i < num_pages * jump; i += jump)
        {
            arr[i] += 1;
        }
        loop -= 1;
    }

    gettimeofday(&end, NULL);

    int elapsed = ((end.tv_sec * 1000000 + end.tv_usec) -
            (start.tv_sec * 1000000 + start.tv_usec));
    float elapsed_avg = elapsed / ((float)num_trials * num_pages);

    printf("time taken for one page access when %d pages are accesed" 
    "on avg is %f\n", num_pages, elapsed_avg);

    return 0;
}