#pragma once
#include <deque>
#include <algorithm>
#include "pcb.h"

void fifo(std::deque<pcb*> rq);
void sjf(std::deque<pcb*> rq);
void rr(std::deque<pcb*> rq);