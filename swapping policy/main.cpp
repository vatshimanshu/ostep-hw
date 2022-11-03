#include<iostream>
#include "fifo.h"
#include "lru.h"
using namespace std;

int main()
{
    int cache_size;
    string policy;
    int num_pages;

    cout << "Welcome to CS5600 Page Replacement simulator.\n";
    cout << "Please enter the size of page cache in the system:\n";
    cin >> cache_size;

    cout << "Please enter the page replacement policy either FIFO or " 
    "LRU:\n";
    cin >> policy;

    cout << "Please enter the number of pages to access:\n";
    cin >> num_pages;

    int pages[num_pages];
    cout << "Please enter the pages to access:\n";
    for (int i = 0; i < num_pages; i++) {
        cin >> pages[i];    
    }

    if (policy.compare("FIFO") == 0)
    {
        FIFO f = FIFO(cache_size);
        for (int i = 0; i < num_pages; i++)
        {
            f.access_page(pages[i]);
        }
    }

    if (policy.compare("LRU") == 0)
    {
        LRU f = LRU(cache_size);
        for (int i = 0; i < num_pages; i++)
        {
            f.access_page(pages[i]);
        }
    }

    return 0;
}