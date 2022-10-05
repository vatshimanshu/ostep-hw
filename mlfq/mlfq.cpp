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

void MLFQ::add_job(Process* p, bool boost)
{
    if (!boost) {
        cout << "Process: " << p->pid << " has entered the system\n";
    }
    else {
        cout << "Process: " << p->pid << " has been boosted\n";
    }

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
            add_job(curr, true);
        }
    }
}

int MLFQ::run_quanta(int curr_time) {
    for (int i = 0; i <= QUEUE_END; i++) {
        if(!mlfq[i].empty()) {
            cout << "current state of mlfq\n";
            MLFQ::print();
            Process* curr = mlfq[i].front();
            mlfq[i].pop();
            int run_time = curr->run_process(timeQuanta[i], curr_time);
            if (i < QUEUE_END and curr->remaining_time > 0) {
                mlfq[i+1].push(curr);
                curr->set_curr_q(i+1);
            }
            else if (curr->remaining_time > 0)
            {
                mlfq[i].push(curr);
            }
            return run_time;
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
            cout << "process id:"<<t->pid<<" start time:"<<t->start_time<< " run time:" <<t->run_time<<" remaining time:"<<t->remaining_time<<"\n";
            copy.pop();
        }
    }
}
