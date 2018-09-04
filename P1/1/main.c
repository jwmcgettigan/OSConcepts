#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int summation(int sum, int num[], int n) {
    for(int i = 0; i < n; i++){sum += num[i];}
    return sum;
}

int main(int argc, char *argv[]) {
    int p[2], sum, num[] = {2,3,7,-1,10,6};
    pipe(p);
    printf("I am the parent with process ID:%d.\n", (int)getpid());
    if (fork() != 0) { // parent goes down this path (main)
        close(p[1]); /*Closes up output side of pipe*/
        read(p[0], &sum, sizeof(sum)); /*Read in the sum from the pipe*/
        printf("I am the parent with process ID:%d with a final sum of %d.\n", (int)getpid(), sum);
    } else { // child (new process)
        sum = summation(0, num, (sizeof(num)/sizeof(num[0])));
        printf("I am the child with process ID:%d and I am sending %d to my parent.\n", (int)getpid(), sum);
        close(p[0]); /*Closes up input side of pipe*/
        write(p[1], &sum, sizeof(sum)); /*Send the sum through the outside of pipe*/
        exit(0);
    } return 0;
}
