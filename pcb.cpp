#include "pcb.h"

pcb::pcb(osp2023::id_type id, osp2023::time_type total_time) {
  this->id = id;
  this->total_time = total_time;
  // this->time_used = osp2023::time_not_set;
  // this->total_wait_time = osp2023::time_not_set;
}

// pcb::pcb(osp2023::id_type id, osp2023::time_type total_time, osp2023::time_type time_used, osp2023::time_type total_wait_time) {
//   this->id = id;
//   this->total_time = total_time;
//   this->time_used = time_used;
//   this->total_wait_time = total_wait_time;
// }