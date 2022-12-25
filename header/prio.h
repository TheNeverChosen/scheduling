#ifndef PRIO_H
#define PRIO_H

#include "scheduler.h"
#include "process.h"
#include <queue>
#include <vector>
#include <string>

class _Cmp_Prio{
public:
  bool operator()(Process *x, Process *y);
};

class Prio : SchedulerPreemp{
private:
  std::priority_queue<Process*, std::vector<Process*>, _Cmp_Prio> ready;

public:
  Prio(std::vector<Process> &processList, long long quantum);

  virtual bool has_ready() override;
  bool process_set_ready(Process *p) override;
  
  Process* get_next_process() override;
  std::string get_name() override;
};

#endif