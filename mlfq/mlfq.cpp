#include<iostream>
#include "mlfq.h"

using namespace std;

MLFQ::MLFQ() {

}

MLFQ::MLFQ(int *timeQ, int timeB)
{
    timeBoost = timeB;
    timeQuanta = timeQ;
}

void MLFQ::add_job(Process* p)
{
    mlfq[0].push(p);
    p->set_curr_q(0);
}

void MLFQ::boost() {
    for (int i = 1; i <= QUEUE_END; i++)
    {
        while (!mlfq[i].empty())
        {
            Process *curr = mlfq[i].front();
            mlfq[i].pop();
            add_job(curr);
        }
    }
}

int MLFQ::run_quanta() {
    for (int i = 0; i <= QUEUE_END; i++) {
        if(!mlfq[i].empty()) {
            Process* curr = mlfq[i].front();
            mlfq[i].pop();
            if (curr->remaining_time > timeQuanta[i]) {
                curr->run_process(timeQuanta[i]);
                if (i < QUEUE_END) {
                    mlfq[i+1].push(curr);
                    curr->set_curr_q(i+1);
                }
                else {
                    mlfq[i].push(curr);
                }
                MLFQ::print();
                return timeQuanta[i];
            }
            else {
                MLFQ::print();
                return curr->remaining_time;
            }
        }
    }
    return -1;
}

void MLFQ::print() {
    for (int i = 0; i <= QUEUE_END; i++)
    {
        std::queue<Process*> copy = mlfq[i];
        cout << "current contents of queue "<< i <<"\n";
        while (!copy.empty())
        {
            Process *t = copy.front();
            cout << "process id:"<<t->pid<<" start time:"<<t->start_time<< " run time:" <<t->run_time<<"remaining time:"<<t->remaining_time<<"\n";
            copy.pop();
        }
    }
}
