#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <exception>

typedef enum{CPU_BOUND=1, IO_BOUND=2, BOTH=3}PType;
typedef enum{PST_NEW=0, PST_READY, PST_RUNNING, PST_SUSPENDED, PST_TERMINATED}PState;
typedef enum{PEV_SET_READY=0, PEV_RUN, PEV_SUSPEND, PEV_TERMINATE}PEvent;

std::string PState_to_string(PState st);

class Exception : public std::exception{
  std::string _msg;
public:
  Exception(const std::string& msg) : _msg(msg){}

  virtual const char* what() const noexcept override{
    return _msg.c_str();
  }
}; 


//Class representing the processes
class Process{
private:
  long long pId,         // Process id
    arrivalTime,         // Arrival time as 'ready'
    totalLen,            // Process Total Length (total time units to terminate),
    priority;            // Process Priority (Bigger is Greater)
  PType type;            // CPU, IO or BOTH
  PState state;          // NEW, READY, RUNNING, SUSPENDED or TERMINATED

  long long firstRunTime, // Time of Process first run (-1 while not executed)
    remainingLen,      // Remaining length (current time units to terminate)
    endTime;              // Process end (-1 while not terminated)

public:
  //Process Constructor
  Process(long long pId, long long arrivalTime, long long length, long long priority, PType type);

  //Returns whether the process was ever executed
  bool is_executed();

  //Returns whether the process is terminated
  bool is_terminated();
  
  /* Handles events and state changes
   * Returns: true->valid event and state change, false->invalid */
  bool handle_event(PEvent e, long long time);

  // Handles execution by a time. Returns: true->ended, false->still standing
  long long execute_time(long long curTime, long long timeProcessed);

  //Returns the process response time (-1 while not executed)
  long long get_time_response();

  //Returns the process turnaround time (-1 if not terminated yet)
  long long get_time_turnaround();

  //Returns the process wait time (-1 if not terminated yet)
  long long get_time_wait();

  //Getters
  long long get_pid();
  long long get_total_length();
  long long get_remaining_length();
  long long get_arrivalTime();
  long long get_priority();
  PState get_state();
};


#endif