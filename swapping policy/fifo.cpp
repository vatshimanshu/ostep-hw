#include<iostream>
#include "fifo.h"
using namespace std;

FIFO::FIFO(int cache_size)
{
    capacity = cache_size;
}

bool FIFO::contains(int page) {
    if (fifo_page_q.empty()) {
        return false;
    }

    queue<int> q = fifo_page_q;
    while (!q.empty())
    {
        if (page == q.front()) {
            return true;
        }

        q.pop();
    }

    return false;
}

void FIFO::print_queue()
{
    queue<int> q = fifo_page_q;
    cout << " |q:";
    while (!q.empty())
    {
        cout << '\t' << q.front();
        q.pop();
    }
    cout << "\n";
}

void FIFO::access_page(int page) {
    cout << "Access: " << page;

    if (contains(page))
    {
        cout << "| Hit  ";
        print_queue();
        return;
    }

    cout << "| Miss ";
    if (fifo_page_q.empty() || fifo_page_q.size() < capacity)
    {
        fifo_page_q.push(page);
    }

    else {
        //cout << "|Replaced: " << fifo_page_q.front();
        fifo_page_q.pop();
        fifo_page_q.push(page);
    }

    print_queue();
    return;
}