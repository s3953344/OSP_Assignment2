#pragma once
#include <deque>
#include <algorithm>
#include "pcb.h"

void fifo(std::deque<pcb*> rq, osp2023::time_type quantum);
void sjf(std::deque<pcb*> rq, osp2023::time_type quantum);
void rr(std::deque<pcb*> rq, osp2023::time_type quantum);