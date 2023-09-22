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
void fifo(std::deque<pcb*> rq, osp2023::time_type quantum) {
  // first process has 0 wait time
  rq.front()->total_wait_time = 0;
  rq.front()->time_used = rq.front()->total_time;

  // update time values for each process
  for (long unsigned int i = 1; i < rq.size(); ++i) {
    // each process waits for every process before it
    rq.at(i)->total_wait_time = rq.at(i - 1)->total_wait_time + rq.at(i - 1)->time_used;
    // time used is the same as the burst time because the job must finish
    rq.at(i)->time_used = rq.at(i)->total_time;
    rq.at(i)->response_time = rq.at(i)->total_wait_time;
    rq.at(i)->turnaround = rq.at(i)->total_wait_time + rq.at(i)->total_time;
  }

  // // calculate totals
  // osp2023::time_type avgWait = totalWait / (osp2023::time_type) rq.size();
  // osp2023::time_type avgTA = totalTA / (osp2023::time_type) rq.size();

  // // display total stats
  // cout << "Average waiting time: " << avgWait << endl;
  // cout << "Average response time: " << avgWait << endl;
  // cout << "Average turnaround time: " << avgTA << endl;
}

/**
  * SJF CALCULATIONS
  * For SJF, sort the queue (stable) and use FIFO
*/
void sjf(std::deque<pcb*> rq, osp2023::time_type quantum) {
  // sort the processes in the ready queue
  std::stable_sort(rq.begin(), rq.end(), [](const pcb* lhs, const pcb* rhs) {
    return lhs->total_time < rhs->total_time;
  });

  // Then from now on, same calculations as FIFO
  fifo(rq, quantum);
}

/**
 * RR CALCULATIONS
 * Note: if a process finishes before using all of its quantum, the next process starts immediately
*/
void rr(std::deque<pcb*> rq, osp2023::time_type quantum) {
  int size = rq.size();
  // int i = 0;
  osp2023::time_type currentTime = 0;

  // make a temp copy
  std::deque<pcb*> tempRq(rq);
  rq.clear();

  // // properly clear elements in rq
  // for (int i = size; i > -1; --i) {
  //   // delete rq.at(i);
  //   // rq.pop_back();
  //   cout << rq.at(i)->id << endl;
  // }

  // for (int i = 0; i < size; i++) {
  //   cout << tempRq.at(i)->id << endl;
  // }

  while (tempRq.size() > 0) {
    if (tempRq.front()->first_run_time == osp2023::time_not_set) {
      tempRq.front()->first_run_time = currentTime;
    }

    // job finishes within quantum
    if (tempRq.front()->total_time - tempRq.front()->time_used - quantum <= 0) {
      // start next job immediately
      currentTime += tempRq.front()->total_time - tempRq.front()->time_used;
      tempRq.front()->completion_time = currentTime;
      // add to finished processes queue
      rq.push_back(tempRq.front());
      tempRq.pop_front();
    } else {
      // job does not finish within quantum
      pcb* tmp = tempRq.front();
      tmp->time_used += quantum;
      currentTime += quantum;
      tempRq.pop_front();
      // add to the back of queue
      tempRq.push_back(tmp);
    }

  }

  // calculate turnaround, waiting, response times
  for (int i = 0; i < rq.size(); ++i) {
    rq.at(i)->turnaround = rq.at(i)->completion_time;
    rq.at(i)->total_wait_time = rq.at(i)->turnaround - rq.at(i)->total_time;
    rq.at(i)->response_time = rq.at(i)->first_run_time;
  }

  // while (jobsRemaining != 0) {
  //   // initialise start times
  //   if (rq.at(i)->start_time == osp2023::time_not_set) {
  //     rq.at(i)->start_time = currentTime;
  //   }

  //   // skip over jobs that are finished
  //   if (rq.at(i)->time_used != rq.at(i)->total_time) {
  //     // job finishes within quantum
  //     if (rq.at(i)->total_time - rq.at(i)->time_used - quantum <= 0) {
  //       // start next job immediately
  //       currentTime += quantum - rq.at(i)->total_time;
  //       rq.at(i)->completion_time = currentTime;
  //       --jobsRemaining;
  //     } else {
  //       // job does not finish within quantum
  //       rq.at(i)->time_used += quantum;
  //     }
  //   }

  //   // increment and loops i
  //   ++i;
  //   if (i == rq.size()) {
  //     i = 0;
  //   }
  // }

}