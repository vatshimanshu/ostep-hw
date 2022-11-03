#include <iostream>
#include "lru.h"
using namespace std;

LRU::LRU(int cache_size)
{
    capacity = cache_size;
}

bool LRU::contains(int page)
{
    if (lru_page_q.empty())
    {
        return false;
    }

    queue<int> q = lru_page_q;
    queue<int> res_q;

    while (!q.empty())
    {
        if (page == q.front())
        {
            q.pop();

            while(!q.empty()) {
                res_q.push(q.front());
                q.pop();
            }
            res_q.push(page);
            
            lru_page_q = res_q;

            return true;
        }

        res_q.push(q.front());
        q.pop();
    }

    return false;
}

void LRU::print_queue()
{
    queue<int> q = lru_page_q;
    cout << " |q:";
    while (!q.empty())
    {
        cout << '\t' << q.front();
        q.pop();
    }
    cout << "\n";
}

void LRU::access_page(int page)
{
    cout << "Access: " << page;

    if (contains(page))
    {
        cout << "| Hit  ";
        print_queue();
        return;
    }

    cout << "| Miss ";
    if (lru_page_q.empty() || lru_page_q.size() < capacity)
    {
        lru_page_q.push(page);
    }

    else
    {
        //cout << "|Replaced: " << fifo_page_q.front();
        lru_page_q.pop();
        lru_page_q.push(page);
    }

    print_queue();
    return;
}