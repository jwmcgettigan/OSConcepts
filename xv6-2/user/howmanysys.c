#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    //printf(1, "There are %d system calls.\n", howmanysys());
    //int* p = (int *) malloc(sizeof(int));
    //printf("Code %p\n", main);
    //printf("Stack %p\n", &p);
    //printf("Heap %p\n", p);
    //*p = 100; (Don't do this!)
    
    //int *p = 0;
    //printf(1, "Hello! %p", &p);
    //int *p = NULL;
    //*p = 20;

    //printf(1, "Bytes stored at address 0: %p\n", *((int*)0));
    int pid = fork();
    if (pid < 0){
	printf(1, "Test Failed!\n");
    }

    else if (pid == 0){
	printf(1, "Test Failed!\n");
    }

    else{
	printf(1, "Test Succeded!\n");
    }

    exit();
}
