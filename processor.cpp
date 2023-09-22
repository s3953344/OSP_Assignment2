#include "processor.h"

using std::deque;
using std::cin;
using std::cout;
using std::endl;
using std::string;

#define ARG_COUNT 2
#define ARG_COUNT_WITH_QUANTUM 3

Processor::Processor() {
  this->datafile = "";
  this->quantum = osp2023::time_not_set;
}

// Processor::Processor(std::string datafile) {
//   this->datafile = datafile;
//   this->quantum = osp2023::time_not_set;
// }

// Processor::Processor(std::string datafile, osp2023::time_type quantum) {
//   this->datafile = datafile;
//   this->quantum = quantum;
// }

bool Processor::processFile(int argc, char** argv) {
  bool isValid = true;
  string datafile;
  string schedule;
  std::ifstream file;
  osp2023::time_type quantum;

  // the ready queue
  this->rq = deque<pcb*>();
  
  // check num of args
  if (argc < ARG_COUNT || argc > ARG_COUNT_WITH_QUANTUM) {
    cout << "Unexpected number of args." << endl;
    cout << "Command should be of form ./{schedule} [quantum] <datafile>" << endl;
    isValid = false;
  } else {
    schedule = argv[0];
  }


  // sjf and fifo must not have 3 args
  if (isValid && argc == ARG_COUNT && schedule == "./rr") {
    isValid = false;
    cout << "Round robin requires ./rr <quantum> <datafile>" << endl;
  }

  // rr must have 3 args
  if (isValid && argc == ARG_COUNT_WITH_QUANTUM && schedule != "./rr") {
    isValid = false;
    cout << "FIFO or SJF must be of form ./{schedule} <datafile>" << endl;
  }

  // set datafile for standard arg count
  if (isValid && argc == ARG_COUNT) {
    datafile = argv[1];
    quantum = osp2023::time_not_set;
  } else if (isValid && argc == ARG_COUNT_WITH_QUANTUM) {
    char* p;
    char* quantumArg = argv[1];
    int base = 10;
    // check if supplied quantum is a number or not
    osp2023::time_type converted = strtol(quantumArg, &p, base);

    // quantum arg supplied is not a number
    if (*p) { 
      isValid = false; 
      cout << "Quantum given is not a number." << endl;
      cout << "Round robin requires ./rr <quantum> <datafile>" << endl;
    }
    // quantum cannot be 0 or negative
    if (isValid && converted <= 0) { 
      isValid = false;
      cout << "Quantum given cannot be 0 or less." << endl;
    }
    
    if (isValid) {
      // set the quantum size
      quantum = converted;
      datafile = argv[2];
    }
  }

  // check for valid data filepath
  if (isValid) {
    file.open(datafile);
      if (!file) {
        isValid = false;
        cout << "Input filepath does not exist." << endl;
      }
  }

  // if all checks pass
  if (isValid) {
    this->datafile = datafile;
    this->quantum = quantum;
    std::ifstream file = std::ifstream(this->datafile);
    string line;
    
    // load in data and create ready queue
    while (getline(file, line)) {
      osp2023::id_type pid = getId(line);
      osp2023::time_type burstTime = getBurstTime(line);
      rq.push_back(new pcb(pid, burstTime));
    }
    return true;
  }

  return false;
}

/**
 * @param line A string which should have a single delimeter character ','
 * @return the id, aka, the first part of the delimited string. If there is no delimeter, then the number is assumed to be the id
*/
osp2023::id_type Processor::getId(string line) {
  string pid;
  int length = line.length();
  int index = 0;
  while (line[index] != ',' && index < length) {
    pid += line[index];
    ++index;
  }

  return (osp2023::id_type) std::stoi(pid);
}

/**
 * @param line A string which should have a single delimeter character ','
 * @return the burst time, aka, the second part of the delimited string.
 * if the delimeter does not exist, then it returns osp2023::time_not_set
*/
osp2023::time_type Processor::getBurstTime(string line) {
  const size_t startPos = line.find(',');
  if (startPos != string::npos) {
    // delimeter character is found
    string burstTime =  line.substr(startPos + 1, line.length() - startPos);
    return (osp2023::time_type) std::stoi(burstTime);
  } else {
    // delimeter character is not found so time is not set
    return osp2023::time_not_set;
  }
}

void Processor::runSchedule(void (*schedule)(std::deque<pcb*> rq)) {
  schedule(this->rq);
}