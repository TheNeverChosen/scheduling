#include "process.h"
#include <string>
#include <iostream>

using namespace std;

std::string PState_to_string(PState st){
  string states[]={"PST_NEW", "PST_READY", "PST_RUNNING", "PST_SUSPENDED", "PST_TERMINATED"};

  return (st<PST_NEW || st>PST_TERMINATED) ? "" : states[int(st)];
}

Process::Process(long long pId, long long arrivalTime, long long totalLen, long long priority, PType type):
  pId(pId), arrivalTime(arrivalTime), totalLen(totalLen), priority(priority), type(type),
  state(PST_NEW), firstRunTime(-1), remainingLen(totalLen), endTime(-1){ }

bool Process::is_executed(){
  return firstRunTime>=0;
}

bool Process::handle_event(PEvent e, long long time){
  switch(e){
    case PEV_SET_READY:
      if(remainingLen<=0 ||
         (state==PST_NEW && arrivalTime>time) ||
         (state!=PST_NEW && state!=PST_RUNNING && state!=PST_SUSPENDED))
        throw Exception("Error PEV_SET_READY");
      state=PST_READY;
      return true;
    case PEV_RUN:
      if(state!=PST_READY) throw Exception("Error PEV_RUN");
      state=PST_RUNNING;
      if(!is_executed()) firstRunTime=time;
      return true;
    case PEV_SUSPEND:
      if(state!=PST_RUNNING || remainingLen<=0) throw Exception("Error PEV_SUSPEND");
      state=PST_SUSPENDED;
      return true;
    case PEV_TERMINATE:
      if(state!=PST_RUNNING || remainingLen>0) throw Exception("Error PEV_TERMINATE: ");
      state=PST_TERMINATED;
      endTime=time;
      return true;
    default: return false;
  }

  return false;
}

long long Process::execute_time(long long curTime, long long timeProcessed){
  if(state!=PST_READY) throw Exception("Error: can't execute process "+to_string(pId)+". Process must be PST_READY, but it's "+PState_to_string(state));

  handle_event(PEV_RUN, curTime);

  timeProcessed=min(max(0LL, timeProcessed), remainingLen);
  remainingLen-=timeProcessed;
  // printf("executed %lld / lasted %lld\n", timeProcessed, remainingLen);

  if(remainingLen<=0) handle_event(PEV_TERMINATE, curTime+timeProcessed);

  return timeProcessed;
}

long long Process::get_time_response(){
  return is_executed() ? firstRunTime-arrivalTime : -1;
}

long long Process::get_time_turnaround(){
  return state==PST_TERMINATED ? endTime-arrivalTime : -1;
}

long long Process::get_time_wait(){
  long long turnaround=get_time_turnaround();
  return turnaround>=0 ? turnaround-totalLen : -1;
}

long long Process::get_pid(){return pId;}
long long Process::get_total_length(){return totalLen;}
long long Process::get_remaining_length(){return remainingLen;}
long long Process::get_arrivalTime(){return arrivalTime;}
long long Process::get_priority(){return priority;}
PState Process::get_state(){return state;}