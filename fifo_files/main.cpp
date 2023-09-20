#include <iostream>
#include <fstream>
#include <queue>
#include "../types.h"
#include "../pcb.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::queue;

#define ARG_COUNT 2

osp2023::id_type getId(string line);
osp2023::time_type getBurstTime(string line);

int main(int argc, char** argv) {
  bool isValid = true;
  string datafile;
  std::ifstream file;
  queue<pcb*> readyQueue;
  

  if (argc != ARG_COUNT) {
    cout << "Unexpected number of args." << endl;
    cout << "Command should be of form ./fifo <datafile>" << endl;
    isValid = false;
  }

  if (isValid) {
    datafile = argv[1];
    file.open(datafile);
      if (!file) {
        isValid = false;
        cout << "Input filepath does not exist." << endl;
      }
  }


  if (isValid) {
    std::ifstream file = std::ifstream(datafile);
    string line;
    // file.open(datafile);
    // create ready queue
    while (getline(file, line)) {
      osp2023::id_type pid = getId(line);
      osp2023::time_type burstTime = getBurstTime(line);
      readyQueue.push(new pcb(pid, burstTime));
    }

    /*
     * FIFO CALCULATIONS
    */
    readyQueue.front()->total_wait_time = 0;
    


    // int size = readyQueue.size();
    // for (int i = 0; i < size; i++) {
    //   cout << readyQueue.front()->id << " burst time: " << readyQueue.front()->total_time << endl;
    //   readyQueue.pop();
    // }
  }

  return EXIT_SUCCESS;
}



osp2023::id_type getId(string line) {
  string pid;
  int length = line.length();
  int index = 0;
  while (line[index] != ',' && index < length) {
    pid += line[index];
    ++index;
  }

  return (osp2023::id_type) std::stoi(pid);
}

osp2023::time_type getBurstTime(string line) {
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