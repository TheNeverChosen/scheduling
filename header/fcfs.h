#ifndef FCFS_H
#define FCFS_H

#include "scheduler.h"
#include "process.h"
#include <queue>
#include <vector>
#include <string>

class FCFS : SchedulerCoop{
private:
  std::queue<Process*> ready;

public:
  FCFS(std::vector<Process> &processList);

  virtual bool has_ready() override;
  bool process_set_ready(Process *p) override;

  Process* get_next_process() override;
  std::string get_name() override;
};

#endif