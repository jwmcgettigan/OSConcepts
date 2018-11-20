#include "types.h"
#include "stat.h"
#include "user.h"

// running system call howmanysys()
int main(void)
{
    printf(1, "There are %d system calls.\n", howmanysys());
    exit();
}
