#include "pcb.h"

pcb::pcb(osp2023::id_type id, osp2023::time_type total_time) {
  this->id = id;
  this->total_time = total_time;
  this->time_used = osp2023::time_not_set;
  this->total_wait_time = osp2023::time_not_set;
  this->turnaround = osp2023::time_not_set;
  this->response_time = osp2023::time_not_set;
  this->first_run_time = osp2023::time_not_set;
  this->completion_time = osp2023::time_not_set;
}