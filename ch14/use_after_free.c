#include<stdio.h>
#include<stdlib.h>

int main() {
	int x;
	int *data = malloc(100*sizeof(int));
	free(data);
	printf("value of data at index 10:%d\n", data[10]);
	return 0;
}
