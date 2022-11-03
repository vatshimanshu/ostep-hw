#ifndef LRU_H
#define LRU_H
#include <queue>

class LRU
{
public:
    int capacity;
    std::queue<int> lru_page_q;

    LRU(int cache_size);
    void access_page(int page);
    void print_queue();
    bool contains(int page);
};

#endif