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

void Process::run_process(int time_run)
{
    remaining_time -= time_run;
}

void Process::set_curr_q(int q)
{
    curr_q = q;
}

void Process::print() {
    std::cout << "process id:" << pid << " start time:"<<start_time << " remaining time:"<<remaining_time<<"\n";
}