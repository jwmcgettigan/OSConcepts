#include "types.h"
#include "stat.h"
#include "user.h"

// running system call howmanysys()
int main(int argc, char *argv[])
{
    if(!strcmp(argv[1], "nullptr"))
      printf(1, "Read byte at address 0: %p\n", *((int*)0));
    else
      printf(1, "There are %d system calls.\n", howmanysys());
    exit();
}
