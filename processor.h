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
  
  private:
    std::string datafile;
    osp2023::time_type quantum; 
    bool processFile(int argc, char** argv);
    osp2023::id_type getId(string line);
    osp2023::time_type getBurstTime(string line);
    deque<pcb*> rq;
};