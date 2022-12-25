#include "scheduler.h"
#include <vector>
#include <algorithm>

using namespace std;

//Default Scheduler's constructor
Scheduler::Scheduler(std::vector<Process> &processList)
  :processList(processList), curTime(0){
  sort(processList.begin(), processList.end(),
    [](Process &a, Process &b){
      return a.get_arrivalTime()!=b.get_arrivalTime()
        ? a.get_arrivalTime()<b.get_arrivalTime()
        : a.get_pid()<b.get_pid();
    });
}

size_t Scheduler::sync_arrives(size_t i){
  for(;i<processList.size() && processList[i].get_arrivalTime()<=curTime;i++)
    process_set_ready(&processList[i]);
  return i;
}

void Scheduler::run_scheduler(){
  Process *executed=nullptr;

  for(size_t i=0;i<processList.size() || has_ready() || executed!=nullptr;){
    i=sync_arrives(i); //handling the process arrival before resuming execution
    process_set_ready(executed); //reinserting the process executed previously (if exists)
    executed=nullptr;

    if(has_ready()){
      executed=get_next_process();
      run_process(executed);
      printf("P%lld\n", executed->get_pid());

      if(executed->get_state()==PST_TERMINATED)
        executed=nullptr;
    }
    else curTime=processList[i].get_arrivalTime();
  }
}

long long Scheduler::get_curTime(){ return curTime; }

double Scheduler::get_average_turnaround(){
  double time=0;
  for(auto p:processList)
    time+=p.get_time_turnaround();
  return time/processList.size();
}

double Scheduler::get_average_wait(){
  double time=0;
  for(auto p:processList)
    time+=p.get_time_wait();
  return time/processList.size();
}

//=====================SchedulerCoop=====================

SchedulerCoop::SchedulerCoop(vector<Process> &processList)
  :Scheduler(processList){}

void SchedulerCoop::run_process(Process *p){
  curTime+=p->execute_time(curTime, p->get_total_length());
}

//====================SchedulerPreemp====================

SchedulerPreemp::SchedulerPreemp(vector<Process> &processList, long long quantum)
  :Scheduler(processList), quantum(quantum){}

void SchedulerPreemp::run_process(Process *p){
  curTime+=p->execute_time(curTime, quantum);
}