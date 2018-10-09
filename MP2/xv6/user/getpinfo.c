#include "types.h"
#include "stat.h"
#include "user.h"
#include "../kernel/pstat.h"

void print_pstat(struct pstat* ps)
{
  for(int i = 0; i < NPROC; i++){
    if(ps->inuse[i] == 1){
      printf(1, "PID %d, ", ps->pid[i]);
      printf(1, "INUSE %d, ", ps->inuse[i]);
      printf(1, "TICKS %d, ", ps->ticks[i]);
      printf(1, "TICKETS %d, \n", ps->tickets[i]);
    }
  }
}

// running system call getpinfo()
int main(void)
{
  printf(1, "Sleeping...\n");
  sleep(100);
  printf(1, "Starting getpinfo...\n");
  struct pstat* ps;
  ps = malloc(sizeof(*ps));
  settickets(20);
  getpinfo(ps);
  print_pstat(ps);

  while(wait() > 0);
  exit();
}
