#include "schedules.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::deque;

/**
  * FIFO CALCULATIONS
  * For FIFO
  * Turnaround time = wait time + total time
  * Response time = wait time
*/
void fifo(std::deque<pcb*> rq) {
  // first process has 0 wait time
  rq.front()->total_wait_time = 0;
  rq.front()->time_used = rq.front()->total_time;

  // update time values for each process
  for (long unsigned int i = 1; i < rq.size(); ++i) {
    // each process waits for every process before it
    rq.at(i)->total_wait_time = rq.at(i - 1)->total_wait_time + rq.at(i - 1)->time_used;
    // time used is the same as the burst time because the job must finish
    rq.at(i)->time_used = rq.at(i)->total_time;
  }

  osp2023::time_type totalWait = 0;
  osp2023::time_type totalTA = 0;

  for (long unsigned int i = 0; i < rq.size(); ++i) {
    // update totals
    totalWait += rq.at(i)->total_wait_time;
    totalTA += rq.at(i)->total_wait_time + rq.at(i)->total_time;
    // calculate and display individual stats for each process
    cout << "PID: " << rq.at(i)->id << endl;
    cout << "\twait time: " << rq.at(i)->total_wait_time << endl;
    cout << "\tresponse time: " << rq.at(i)->total_wait_time << endl;
    cout << "\tturnaround: " << rq.at(i)->total_wait_time + rq.at(i)->total_time << endl;
    cout << "----------------------" << endl;
  }

  // calculate totals
  osp2023::time_type avgWait = totalWait / (osp2023::time_type) rq.size();
  osp2023::time_type avgTA = totalTA / (osp2023::time_type) rq.size();

  // display total stats
  cout << "Average waiting time: " << avgWait << endl;
  cout << "Average response time: " << avgWait << endl;
  cout << "Average turnaround time: " << avgTA << endl;
}

/**
  * SJF CALCULATIONS
  * For SJF, sort the queue (stable) and use FIFO
*/
void sjf(std::deque<pcb*> rq) {
  // sort the processes in the ready queue
  std::stable_sort(rq.begin(), rq.end(), [](const pcb* lhs, const pcb* rhs) {
    return lhs->total_time < rhs->total_time;
  });

  // Then from now on, same calculations as FIFO
  fifo(rq);
}