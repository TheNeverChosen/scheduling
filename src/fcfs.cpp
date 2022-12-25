#include "fcfs.h"
#include "process.h"
#include <queue>
#include <vector>

using namespace std;

FCFS::FCFS(vector<Process> &processList):SchedulerCoop(processList){}

bool FCFS::has_ready(){return !ready.empty();}

bool FCFS::process_set_ready(Process *p){
  if(p==nullptr || !p->handle_event(PEV_SET_READY, curTime)) return false;
  ready.push(p); return true;
}

Process* FCFS::get_next_process(){
  if(!has_ready()) return nullptr;
  Process *p = ready.front(); ready.pop();
  return p;
}

string FCFS::get_name(){
  return "FCFS";
}