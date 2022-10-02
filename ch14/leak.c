#include<stdio.h>
#include<stdlib.h>

int main() {
	int *p;
	p = malloc(4*sizeof(int));

	printf("address of p, %p\n", p);
	return 0;
}
