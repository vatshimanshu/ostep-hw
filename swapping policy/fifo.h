#ifndef FIFO_H
#define FIFO_H
#include<queue>

class FIFO
{
public:
    int capacity;
    std::queue<int> fifo_page_q;

    FIFO(int cache_size);
    void access_page(int page);
    void print_queue();
    bool contains(int page);
};

#endif