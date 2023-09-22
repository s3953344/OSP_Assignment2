#include <iostream>
#include <fstream>
#include <deque>
#include "../types.h"
#include "../pcb.h"
#include "../processor.h"
#include "../schedules.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::deque;

/**
 * Write the functions that select which process to run next and load the corresponding PCB. 
With this scheme, the process that requests the CPU first is allocated the CPU first. We finish the first 
process before moving onto the next and so on. As all processes arrive at time 0, you may follow the 
sequence given by the generated datafile for execution.
*/
int main(int argc, char** argv) {
  Processor processor = Processor();
  bool success = processor.processFile(argc, argv);
  if (success) processor.runSchedule(&fifo);

  return EXIT_SUCCESS;
}