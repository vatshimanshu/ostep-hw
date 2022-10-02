#include<stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int mem, time = 0;
    if (argc < 2)
    {
        printf("This program expects atleast one argument. Please" 
        " specify the number of megabytes to be used\n");
        return 0;
    }
    else if (argc == 2) {
        mem = atoi(argv[1]);
    }
    else {
        mem = atoi(argv[1]);
        time = atoi(argv[2]);
    }

    char *arr = calloc(mem, 1000000 * sizeof(char));

    if (time == 0){
        while(1){
            for (int i = 0; i < 1000000 * mem; i++)
            {
                char c = arr[i];
            }
        }
    }

    return 0;
}