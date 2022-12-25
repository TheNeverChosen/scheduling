#include "rr.h"
#include "process.h"
#include <queue>
#include <vector>

using namespace std;

RR::RR(vector<Process> &processList, long long quantum)
  :SchedulerPreemp(processList, quantum){}

bool RR::has_ready(){return !ready.empty();}

bool RR::process_set_ready(Process *p){
  if(p==nullptr || !p->handle_event(PEV_SET_READY, curTime)) return false;
  ready.push(p); return true;
}

Process* RR::get_next_process(){
  if(!has_ready()) return nullptr;
  Process *p = ready.front(); ready.pop();
  return p;
}

string RR::get_name(){
  return "RR";
}