#include<stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    usleep(5);
    gettimeofday(&end, NULL);

    printf("Time taken waiting is : %ld micro seconds\n",
           ((end.tv_sec * 1000000 + end.tv_usec) -
            (start.tv_sec * 1000000 + start.tv_usec)));

    return 0;
}
