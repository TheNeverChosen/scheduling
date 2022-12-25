#include "sjf.h"
#include "process.h"
#include <queue>
#include <vector>

using namespace std;

bool _Cmp_SJF::operator()(Process *x, Process *y){
  return x->get_remaining_length() != y->get_remaining_length()
    ? x->get_remaining_length() > y->get_remaining_length()
    : x->get_pid() > y->get_pid();
};

SJF::SJF(vector<Process> &processList):SchedulerCoop(processList){}

bool SJF::has_ready(){return !ready.empty();}

bool SJF::process_set_ready(Process *p){
  if(p==nullptr || !p->handle_event(PEV_SET_READY, curTime)) return false;
  ready.push(p); return true;
}

Process* SJF::get_next_process(){
  if(!has_ready()) return nullptr;
  Process *p = ready.top(); ready.pop();
  return p;
}

string SJF::get_name(){
  return "SJF";
}