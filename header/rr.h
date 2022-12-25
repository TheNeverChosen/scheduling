#ifndef RR_H
#define RR_H

#include "scheduler.h"
#include "process.h"
#include <queue>
#include <vector>
#include <string>

class RR : SchedulerPreemp{
private:
  std::queue<Process*> ready;

public:
  RR(std::vector<Process> &processList, long long quantum);

  virtual bool has_ready() override;
  bool process_set_ready(Process *p) override;
  
  Process* get_next_process() override;
  std::string get_name() override;
};

#endif