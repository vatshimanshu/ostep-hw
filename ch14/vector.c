#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct vector
{
    /* data */
    int *data;
    int size;
};

void insert(struct vector* vec, int data) {
    int len = vec->size;
    if(len == 0) {
        vec->data = malloc(sizeof(int));
    }
    else {
        vec->data = realloc(vec->data, (len+1) *sizeof(int));
    }

    vec->data[len] = data;
    vec->size += 1;
}

int get_size(struct vector vec)
{
    return vec.size;
}

void print_data(struct vector vec)
{
    for (int i = 0; i < vec.size; i++){
        printf("%d\n", vec.data[i]);
    }
}

int main() {
    struct vector v;
    v.size = 0;

    insert(&v, 1);
    insert(&v, 2);
    insert(&v, 3);

    assert(v.size == 3);
    print_data(v);
    
    free(v.data);

    return 0;
}