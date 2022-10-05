#include<iostream>
#include "mlfq.h"

using namespace std;
int curr_time = 1;

class simulate
{
private:
    MLFQ mlfq;
    Process *job_list;
    int num_jobs;

public:
    simulate(MLFQ mlfq, Process* jobs, int n);
    void run();
};

simulate::simulate(MLFQ queue, Process *jobs, int n)
{
    mlfq = queue;
    job_list = jobs;
    num_jobs = n;
    // sort(job_list)
}

void simulate::run() {
    int added = 0;

    while (1)
    {
        if ((curr_time-1) % mlfq.timeBoost == 0) {
            mlfq.boost();
        }

        for (int i = 0; i < num_jobs; i++)
        {
            //job_list[i].print();
            if (curr_time >= job_list[i].start_time && job_list[i].curr_q == -1)
            {
                mlfq.add_job(&job_list[i], false);
                added += 1;
            }
        }

        int elapsed = mlfq.run_quanta(curr_time);
        if (elapsed == -1 && added == num_jobs)
        {
            break;
        }

        if (elapsed == -1) {
            curr_time += 1;
        }
        else {
            curr_time += elapsed;
        }
    }
}

int main() {
    int time_boost = 50;
    int time_quanta[] = {10, 10, 10};

    MLFQ mlfq = MLFQ(time_quanta, time_boost);
    cout << "Welcome to CS5600 MLFQ simulator.\n";
    cout << "Enter the number of jobs in the system followed by the start time, run time, and id of each job\n";

    int num_jobs;
    cin >> num_jobs;
    Process jobs[num_jobs];

    for (int i = 0; i < num_jobs; i++)
    {
        int start_time, run_time, id;
        cin >> start_time >> run_time >> id;
        jobs[i] = Process(id, start_time, run_time, 0);
    }

    simulate s = simulate(mlfq, jobs, num_jobs);
    s.run();

    return 0;
}