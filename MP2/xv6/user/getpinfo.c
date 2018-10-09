#include "types.h"
#include "stat.h"
#include "user.h"
#include "../kernel/pstat.h"

void print_pstat(struct pstat* p_stat)
{
  for(int counter = 0; counter < NPROC; counter++){
    if(p_stat->inuse[counter] == 1){
      printf(1, "PID %d, ", p_stat->pid[counter]);
      printf(1, "INUSE %d, ", p_stat->inuse[counter]);
      printf(1, "TICKS %d, ", p_stat->ticks[counter]);
      printf(1, "TICKETS %d, \n", p_stat->tickets[counter]);
    }
  }
}

// running system call getpinfo()
int main(void)
{
  struct pstat* p_stat;
  settickets(30);
  p_stat = malloc(sizeof(*p_stat));

  getpinfo(p_stat);
  print_pstat(p_stat);

  exit();
}
