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
 * Write the functions that select what process to run next, and load the corresponding PCB and add it 
 * back to the ready queue when the process has used up its quantum. 
 * 
 * The round-robin algorithm is such that each process takes its turn using up its quantum until it finishes.
 * The CPU scheduler goes around the ready queue, allocating the CPU to each process for a time 
 * interval of up to 1 time quantum. 
 * 
 * A time quantum is generally from 10 to 100 milliseconds in length. You may choose different quantum 
 * sizes within the range for your experiments. 
*/
int main(int argc, char** argv) {
  Processor processor = Processor();
  bool success = processor.processFile(argc, argv);
  if (success) processor.runSchedule(&rr);

  return EXIT_SUCCESS;
}
