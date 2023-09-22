#include "processor.h"

using std::deque;
using std::cin;
using std::cout;
using std::endl;
using std::string;

#define ARG_COUNT 2

Processor::Processor() {
  this->datafile = "";
  this->quantum = osp2023::time_not_set;
}

Processor::Processor(std::string datafile) {
  this->datafile = datafile;
  this->quantum = osp2023::time_not_set;
}

Processor::Processor(std::string datafile, osp2023::time_type quantum) {
  this->datafile = datafile;
  this->quantum = quantum;
}

bool Processor::processFile(int argc, char** argv) {
  bool isValid = true;
  string datafile;
  std::ifstream file;

  // the ready queue
  this->rq = deque<pcb*>();
  
  // check num of args
  if (argc != ARG_COUNT) {
    cout << "Unexpected number of args." << endl;
    cout << "Command should be of form ./fifo <datafile>" << endl;
    isValid = false;
  }

  // check for valid data filepath
  if (isValid) {
    datafile = argv[1];
    file.open(datafile);
      if (!file) {
        isValid = false;
        cout << "Input filepath does not exist." << endl;
      }
  }

  // if all checks pass
  if (isValid) {
    this->datafile = datafile;
    std::ifstream file = std::ifstream(datafile);
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