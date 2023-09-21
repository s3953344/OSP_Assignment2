#include <iostream>
#include <fstream>
#include <deque>
#include "../types.h"
#include "../pcb.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::deque;

#define ARG_COUNT 2

osp2023::id_type getId(string line);
osp2023::time_type getBurstTime(string line);

int main(int argc, char** argv) {
  bool isValid = true;
  string datafile;
  std::ifstream file;
  // the ready queue
  deque<pcb*> rq = deque<pcb*>();
  

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
      rq.push_back(new pcb(pid, burstTime));
    }

    /*
     * FIFO CALCULATIONS
    */
    rq.front()->total_wait_time = 0;
    rq.front()->time_used = rq.front()->total_time;

    for (int i = 1; i < rq.size(); ++i) {
      rq.at(i)->total_wait_time = rq.at(i - 1)->total_wait_time + rq.at(i - 1)->time_used;
      rq.at(i)->time_used = rq.at(i)->total_time;
      cout << rq.at(i)->total_wait_time << endl;
    }

    cout << "----------------------" << endl;
    
    // osp2023::time_type totalWait;
    int totalWait = 0;
    int avgWait;
    for (int i = 0; i < rq.size(); ++i) {
      totalWait += rq.at(i)->total_wait_time;
    }

    avgWait = totalWait / (osp2023::time_type) rq.size();

    cout << "Average waiting time: " << avgWait << endl;


    // int size = rq.size();
    // for (int i = 0; i < size; i++) {
    //   cout << rq.front()->id << " burst time: " << rq.front()->total_time << endl;
    //   rq.pop();
    // }
  }

  return EXIT_SUCCESS;
}


/**
 * @param line A string which should have a single delimeter character ','
 * @return the id, aka, the first part of the delimited string. If there is no delimeter, then the number is assumed to be the id
*/
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

/**
 * @param line A string which should have a single delimeter character ','
 * @return the burst time, aka, the second part of the delimited string.
 * if the delimeter does not exist, then it returns osp2023::time_not_set
*/
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