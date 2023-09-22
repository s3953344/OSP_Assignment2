#pragma once
#include <iostream>
#include <fstream>
#include <deque>
#include "pcb.h"
#include "types.h"

class Processor {
  public:
    Processor();
    Processor(std::string datafile);
    Processor(std::string datafile, osp2023::time_type quantum);
    void runSchedule(void (*schedule)(std::deque<pcb*> rq));
    bool processFile(int argc, char** argv);
  
  private:
    std::string datafile;
    osp2023::time_type quantum; 
    osp2023::id_type getId(std::string line);
    osp2023::time_type getBurstTime(std::string line);
    std::deque<pcb*> rq;
};