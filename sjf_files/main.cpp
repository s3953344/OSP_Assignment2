#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
#include "../types.h"
#include "../pcb.h"
#include "../processor.h"
#include "../schedules.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::deque;

void sjf(std::deque<pcb*> rq);

/**
 *
This algorithm associates with each process the length of the process’s CPU burst time. When the 
CPU is available, it is assigned to the process that has the smallest CPU burst time. If the CPU burst
times of two processes are the same, FIFO scheduling is used to break the tie.
In this case, insert PCBs to the ready queue in sorted order by CPU burst time, with the shortest 
process as the first and the longest at the last. From there, it is the same algorithm as FIFO. 
*/
int main(int argc, char** argv) {
  Processor processor = Processor();
  bool success = processor.processFile(argc, argv);
  if (success) processor.runSchedule(&sjf);

  return EXIT_SUCCESS;
}

/**
  * SJF CALCULATIONS
  * For SJF
  * Turnaround time = wait time + total time
  * Response time = wait time
*/
void sjf(std::deque<pcb*> rq) {
  // cout << "BEFORE" << endl;
  // for (int i = 0; i < rq.size(); ++i) {
  //   cout << rq.at(i)->total_time << endl;
  // }

  // sort the processes in the ready queue
  std::stable_sort(rq.begin(), rq.end(), [](const pcb* lhs, const pcb* rhs) {
    return lhs->total_time < rhs->total_time;
  });

  // Then from now on, same calculations as FIFO
  fifo(rq);

  
  // Now we can p
  // first process has 0 wait time
  // rq.front()->total_wait_time = 0;
  // rq.front()->time_used = rq.front()->total_time;

  // // update time values for each process
  // for (int i = 1; i < rq.size(); ++i) {
  //   // each process waits for every process before it
  //   rq.at(i)->total_wait_time = rq.at(i - 1)->total_wait_time + rq.at(i - 1)->time_used;
  //   // time used is the same as the burst time because the job must finish
  //   rq.at(i)->time_used = rq.at(i)->total_time;
  // }

  // osp2023::time_type totalWait = 0;
  // osp2023::time_type totalTA = 0;

  // for (int i = 0; i < rq.size(); ++i) {
  //   // update totals
  //   totalWait += rq.at(i)->total_wait_time;
  //   totalTA += rq.at(i)->total_wait_time + rq.at(i)->total_time;
  //   // calculate and display individual stats for each process
  //   cout << "PID: " << rq.at(i)->id << endl;
  //   cout << "\twait time: " << rq.at(i)->total_wait_time << endl;
  //   cout << "\tresponse time: " << rq.at(i)->total_wait_time << endl;
  //   cout << "\tturnaround: " << rq.at(i)->total_wait_time + rq.at(i)->total_time << endl;
  //   cout << "----------------------" << endl;
  // }

  // // calculate totals
  // osp2023::time_type avgWait = totalWait / (osp2023::time_type) rq.size();
  // osp2023::time_type avgTA = totalTA / (osp2023::time_type) rq.size();

  // // display total stats
  // cout << "Average waiting time: " << avgWait << endl;
  // cout << "Average response time: " << avgWait << endl;
  // cout << "Average turnaround time: " << avgTA << endl;
}