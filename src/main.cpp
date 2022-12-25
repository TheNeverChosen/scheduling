#include <bits/stdc++.h>
#include "process.h"
#include "scheduler.h"
#include "rr.h"
#include "prio.h"
#include "fcfs.h"
#include "sjf.h"

using namespace std;

void clear_buffer_file(FILE *f){
  char c;
  while((c=fgetc(f))!='\n' && c!=EOF){}
}

typedef enum{ERR_NO_FILE=1, ERR_CANT_OPEN, ERR_NO_PROCESS, ERR_INVALID_QUANTUM,
  ERR_INVALID_TYPE}Error;

void read_quantum(long long &quantum){
  scanf("%lld", &quantum);
  if(quantum<=0){
    printf("Quantum invalido.");
    exit(ERR_INVALID_QUANTUM);
  }
}

int main(int arg, char *argv[]){
  if(arg<2){
    printf("Arquivo de entrada nao fornecido.\n");
    return ERR_NO_FILE;
  }

  FILE *fIn = fopen(argv[1], "r");

  if(!fIn){
    printf("Arquivo de entrada nao pode ser aberto.\n");
    return ERR_CANT_OPEN;
  }

  vector<Process> processList;
  long long pid, arrivalTime, totalLen, priority;
  int type;
  while(fscanf(fIn, "P%lld %lld %lld %lld %d", &pid, &arrivalTime, &totalLen, &priority, &type)==5){
    processList.emplace_back(pid, arrivalTime, totalLen, priority, (PType)type);
    // printf("P%lld %lld %lld %lld %d\n", pid, arrivalTime, totalLen, priority, type);
    clear_buffer_file(fIn);
  }
  // printf("\n");

  /*
    type 1 - FCFS e SJF
    type 2 - SJF e RR
    type 3 - RR e Prio
  */

  if(processList.empty()){
    printf("Nenhum processo valido para execucao.\n");
    return ERR_NO_PROCESS;
  }

  Scheduler *sch[2];

  printf("Os algoritmos indicados sao: ");
  if(type==1){
    printf("FCFS e SJF.\n");
    sch[0]=(Scheduler*) new FCFS(processList);
    sch[1]=(Scheduler*) new SJF(processList);
  }
  else if(type==2){
    long long quantumRR;
    printf("SJF e RR.\nInforme o quantum para o RR: ");
    read_quantum(quantumRR);
    sch[0]=(Scheduler*) new SJF(processList);
    sch[1]=(Scheduler*) new RR(processList, quantumRR);
  }
  else if(type==3){
    long long quantumRR, quantumPrio;
    printf("RR e Prio.\nInforme o quantum para o RR: ");
    read_quantum(quantumRR);
    printf("Informe o quantum para o Prio: ");
    read_quantum(quantumPrio);
    sch[0]=(Scheduler*) new RR(processList, quantumRR);
    sch[1]=(Scheduler*) new Prio(processList, quantumPrio);
  }
  else{
    printf("Tipo invalido de processo.\n");
    return ERR_INVALID_TYPE;
  }

  for(int i=0;i<2;i++){
    printf("\n==========Execucao do algoritmo %s==========\n", sch[i]->get_name().c_str());
    sch[i]->run_scheduler();
    printf("\nTempo medio de execucao: %lf\nTempo medio de espera: %lf\n",
      sch[i]->get_average_turnaround(), sch[i]->get_average_wait());
  }
  
  fclose(fIn);

  return 0;
}