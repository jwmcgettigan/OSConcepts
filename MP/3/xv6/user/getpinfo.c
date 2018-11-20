#include "types.h"
#include "stat.h"
#include "user.h"
#include "../kernel/pstat.h"

void print_pstat(struct pstat* ps)
{
  for(int i = 0; i < NPROC; i++){
    if(ps->inuse[i] == 1){
      printf(1, "PID %d, ", ps->pid[i]);
      printf(1, "TICKS %d, ", ps->ticks[i]);
      printf(1, "TICKETS %d, \n", ps->tickets[i]);
    }
  }
}

// running system call getpinfo()
int main(void)
{
  struct pstat* ps;
  ps = malloc(sizeof(*ps));
  int i, nChildren = 4, pid[nChildren];
  settickets(5);

  for(i = 0; i < nChildren; i++){
    if((pid[i] = fork()) == 0){
      settickets(i*10);
      for(int k = 1; k < 50000000; k+=2, k--){}
      exit();
    }
  }

  for(int k = 0, t = 0; k < 1000; k++) {
    if(k%100 == 0){
      printf(1, "TIME %d =====================\n", ++t);
      getpinfo(ps);
      print_pstat(ps);
    }
  }
  for(i = 0; i < nChildren; i++)
    kill(pid[i]);
  while(wait() > 0);
  exit();
}
