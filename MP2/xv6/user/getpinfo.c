#include "types.h"
#include "stat.h"
#include "user.h"
#include "../kernel/pstat.h"

void print_pstat(struct pstat* ps)
{
  //printf(1, "PID, TICKS, TICKETS\n");
  for(int i = 0; i < NPROC; i++){
    if(ps->inuse[i] == 1){
      printf(1, "PID %d, ", ps->pid[i]);
      printf(1, "TICKS %d, ", ps->ticks[i]);
      printf(1, "TICKETS %d, \n", ps->tickets[i]);
      //printf(1, "%d, %d, %d\n", ps->pid[i], ps->ticks[i], ps->tickets[i]);
    }
  }
}

// running system call getpinfo()
int main(void)
{
  struct pstat* ps;
  ps = malloc(sizeof(*ps));
  int pid[NPROC], i, nChildren = 10;
  settickets(5);

  for(i = 0; i < nChildren; i++){
    if((pid[i] = fork()) == 0){
      settickets(i*10);
      for(int k = 1; k < 50000000; k+=2, k--){}
      exit();
    }
  }
  //while(wait() > 0);
  //getpinfo(ps);
  //print_pstat(ps);

  for(i = 0; i < nChildren; i++){
    printf(1, "=======KILLING CHILD %d=======\n", i+1);
    getpinfo(ps);
    print_pstat(ps);
    kill(pid[i]);
  }
  while(wait() > 0);
  exit();
}
