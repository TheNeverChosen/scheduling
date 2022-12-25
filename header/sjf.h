#ifndef SJF_H
#define SJF_H

#include "scheduler.h"
#include "process.h"
#include <queue>
#include <vector>
#include <string>

class _Cmp_SJF{
public:
  bool operator()(Process *x, Process *y);
};

class SJF : SchedulerCoop{
private:

  std::priority_queue<Process*, std::vector<Process*>, _Cmp_SJF> ready;

public:
  SJF(std::vector<Process> &processList);

  virtual bool has_ready() override;
  bool process_set_ready(Process *p) override;
  
  Process* get_next_process() override;
  std::string get_name() override;
};

#endif