#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
	if (atoi(argv[1]) == 1){
	    int ppid = getpid();
	    int pid = fork();

	    if (pid < 0){
		printf(1, "Test Failed!\n");
		exit();
	    }

	    else if (pid == 0){
		uint * nullp = (uint*)0;
		printf(1, "Null dereference: ");
		printf(1, "%x %x\n", nullp, *nullp);
		printf(1, "Test Failed!\n");
		kill(ppid);
		exit();
	    }

	    else{
		wait();
		printf(1, "Test Succeded!\n");
		exit();
	    }
	}

	else if (atoi(argv[1]) == 2){
	    int ppid = getpid();
	    int pid = fork();

	    if (pid < 0){
		printf(1, "Test Failed!\n");
		exit();
	    }

	    else if (pid == 0){
		uint * badp = (uint*)4095;
		printf(1, "Bad dereference (0x0fff): ");
		printf(1, "%x %x\n", badp, *badp);
		printf(1, "Test Failed!\n");
		kill(ppid);
		exit();
	    }

	    else{
		wait();
	    }

	    printf(1, "Test Succeded!\n");
	    exit();
	}

    exit();
}
