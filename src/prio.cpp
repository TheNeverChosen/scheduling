#include "prio.h"
#include "process.h"
#include <queue>
#include <vector>

using namespace std;

bool _Cmp_Prio::operator()(Process *x, Process *y){
  return x->get_priority() != y->get_priority()
    ? x->get_priority() < y->get_priority()
    : x->get_pid() > y->get_pid();
};

Prio::Prio(vector<Process> &processList, long long quantum)
  :SchedulerPreemp(processList, quantum){}

bool Prio::has_ready(){return !ready.empty();}

bool Prio::process_set_ready(Process *p){
  if(p==nullptr || p->get_priority()<=0 ||
     !p->handle_event(PEV_SET_READY, curTime)) return false;
  ready.push(p); return true;
}

Process* Prio::get_next_process(){
  if(!has_ready()) return nullptr;
  Process *p = ready.top(); ready.pop();
  return p;
}

string Prio::get_name(){
  return "Prio";
} 