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
  if (success) processor.runSchedule(&rr);

  return EXIT_SUCCESS;
}
