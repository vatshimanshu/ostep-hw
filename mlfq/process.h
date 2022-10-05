#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    int pid;
    int start_time;
    int run_time;
    int io_freq;
    int remaining_time;
    int curr_q;

    Process();
    Process(int id, int start, int run, int io);
    void run_process(int time_run);
    void set_curr_q(int q);
    void print();
};

#endif