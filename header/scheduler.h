#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <vector>
#include <string>

class Scheduler{
private:
  std::vector<Process> processList;

  size_t sync_arrives(size_t i);

protected:
  long long curTime; //Current execution time

public:
  //Default Scheduler's constructor
  Scheduler(std::vector<Process> &processList);

  //Verify whether it's some ready process to be executed
  virtual bool has_ready() = 0;

  /*Handles new process arrival to 'ready' state.
   *Returns: true->added to 'ready' successfully, false-> not added*/
  virtual bool process_set_ready(Process *p) = 0;

  virtual Process* get_next_process() = 0;
  virtual void run_process(Process *p) = 0;

  void run_scheduler();

  //Getters:
  long long get_curTime();
  double get_average_turnaround();
  double get_average_wait();
  virtual std::string get_name() = 0;
};

//=====================SchedulerCoop=====================

class SchedulerCoop : public Scheduler{
public:
  SchedulerCoop(std::vector<Process> &processList);
  void run_process(Process *p) override;
};

//====================SchedulerPreemp====================

class SchedulerPreemp : public Scheduler{
protected:
  long long quantum;
public:
  SchedulerPreemp(std::vector<Process> &processList, long long quantum);
  void run_process(Process *p) override;
};

#endif