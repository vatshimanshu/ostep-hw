#include<iostream>
#include "process.h"

Process::Process() {

}

Process::Process(int id, int start, int run, int io)
{
    start_time = start;
    run_time = run;
    remaining_time = run;
    pid = id;
    io_freq = io;
    curr_q = -1;
}

int Process::run_process(int time_run, int curr_time)
{
    for (int i = 0; i < time_run; i++) {
        std::cout << "current time:"<< curr_time+i;
        remaining_time -= 1;
        print();
        if (remaining_time == 0) {
            std::cout << "Process:" << pid <<" has completed execution\n";
            return i+1;
        }
    }
    return time_run;
}

void Process::set_curr_q(int q)
{
    curr_q = q;
}

void Process::print() {
    std::cout << " process id:" << pid << " start time:"<<start_time << " remaining time:"<<remaining_time<<" current queue:"<<curr_q<<"\n";
}