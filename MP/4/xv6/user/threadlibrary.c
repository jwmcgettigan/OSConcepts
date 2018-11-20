#include "types.h"
#include "stat.h"
//#include "fcntl.h"
#include "user.h"
#include "x86.h"

#define PGSIZE (4096)
#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}
void worker(void *arg_ptr);

int global = 0;
int ppid;
lock_t lock;
int num_threads = 30;
int loops = 1000;

int main(int argc, char *argv[]){
    ppid = getpid();

    lock_init(&lock);

    int i;
    for (i = 0; i < num_threads; i++){
	int thread_pid = thread_create(worker, 0);
	assert(thread_pid > 0);
    }

    for (i = 0; i < num_threads; i++){
	int join_pid = thread_join();
	assert(join_pid > 0);
    }

    assert(global == num_threads * loops);
    printf(1, "TEST PASSED\n");
    exit();
}

int thread_create(void (*start_routine)(void*), void *arg){
  void *stack = malloc(PGSIZE * 2);
  if (!stack) {
     printf(1, "Error: malloc failed\n");
     exit();
  }

  if((uint)stack % PGSIZE)
     stack = stack + (4096 - (uint)stack % PGSIZE);

  return clone(start_routine, arg, stack);
}

int thread_join(){
  void* ustack;
  int tpid = join(&ustack);

  if (tpid != -1)
     free(ustack);

  return tpid;
}

void lock_init(volatile lock_t *lock) {
  *lock = 0;
}

void lock_acquire(volatile lock_t *lock) {
  while (xchg(lock, 1) == 1)
    ;
}

void lock_release(volatile lock_t *lock) {
  *lock = 0;
}

void worker(void *arg_ptr){
    int i, j, temp;
    for (i = 0; i < loops; i++){
	lock_acquire(&lock);
	temp = global;
	for (j = 0; j < 50; j++);
	global = temp + 1;
	lock_release(&lock);
    }
    exit();
}
