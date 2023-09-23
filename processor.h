#pragma once
#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
#include "pcb.h"
#include "types.h"

/**
 * A class which loads in data from a datafile
*/
class Processor {
  public:
    Processor();
    // parse command args and load ready queue
    bool processFile(int argc, char** argv);
    // pass in a function (schedule business logic) as a pointer for the processor to run
    void runSchedule(void (*schedule)(std::deque<pcb*> rq, osp2023::time_type quantum));
    
  private:
    std::string datafile;
    osp2023::time_type quantum;
    // the ready queue
    std::deque<pcb*> rq;
    
    osp2023::id_type getId(std::string line);
    osp2023::time_type getBurstTime(std::string line);
    // display individual process results and calculates total averages
    void calculateTimes();
};