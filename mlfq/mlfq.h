#ifndef MLFQ_H
#define MLFQ_H

#include<queue>
#include "process.h"

#define QUEUE_START 0
#define QUEUE_END 2

class MLFQ
{
public:
    int* timeQuanta;
    int timeBoost;
    std::queue<Process*> mlfq[3];

    MLFQ();
    MLFQ(int *timeQ, int timeB);
    void add_job(Process *p, bool boost);
    void boost();
    int run_quanta(int curr_time);
    void print();
};

#endif