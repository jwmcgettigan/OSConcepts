#include "types.h"
#include "stat.h"
#include "user.h"
#define PGSIZE 4096
#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker (void *arg_ptr);

int global = 1;
int ppid;
int main(int argc, char *argv[]){	
	ppid = getpid();	
	void *stack = malloc(PGSIZE * 2);
	assert(stack != NULL);
	if((uint)stack % PGSIZE)
	    stack = stack + (4096 - (uint)stack % PGSIZE);
	int clone_pid = clone(worker, 0, stack);
	assert(clone_pid > 0);
	while(global != 5);
	printf(1, "TEST PASSED\n");
	exit();
}

void worker (void *arg_ptr){
    assert(global == 1);
    global = 5;
    exit();
}


