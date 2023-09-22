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
    // Processor(std::string datafile);
    // Processor(std::string datafile, osp2023::time_type quantum);
    void runSchedule(void (*schedule)(std::deque<pcb*> rq));
    bool processFile(int argc, char** argv);
    
  
  private:
    std::string datafile;
    osp2023::time_type quantum;
    std::deque<pcb*> rq;
    
    osp2023::id_type getId(std::string line);
    osp2023::time_type getBurstTime(std::string line);
    void calculateTimes();
};