#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int summation(int sum, int *num, int n) {
    for(int k = 0; k < n; k++){sum += num[k];}
    return sum;
}

int main(int argc, char *argv[]) {
    int i, sum, pid;
    int p[2], num[] = {2,3,7,-1,10,6};
    int a = atoi(argv[1]), n = (sizeof(num)/sizeof(*num)); /* a = second argument; n = length of array */
    int r = n%a, s = 0, finalSum = 0; /* r = remainder; s = sliceSize; */
    if (argc == 1){printf("Enter the number of children.");
        exit(1);}
    if (a > n || a < 1 ){printf("Error: more children(%d) than array-length(%d)\n", a, n);
        exit(1);}
    printf("I am the parent with process ID:%d.\n", (int)getpid());
    for (i = 0; i < n; i+=s) { /* loops until all slices have been processed */
        if(r > 0){s = (n/a) + 1; r--;} /* if there is a remainder, add 1 to a slice and subtract 1 from the remainder */
        else{s = n/a;}
        pipe(p);
        if ((pid = fork()) == 0) { // child (new process)
            int slice[s]; /* create slice of size s */
            memcpy(slice, &num[i], s*sizeof(*num)); /* copy from num into slice the correct elements */
            sum = summation(0, slice, s);
            printf("I am the child with process ID:%d and my partial summation is: %d.\n", (int)getpid(), sum);
            close(p[0]); /*Closes up pipe input*/
            write(p[1], &sum, sizeof(sum)); /*Send the sum through the pipe output*/
            exit(0);
        } else if (pid > 0) { // parent goes down this path (main)
            close(p[1]); /*Closes up pipe output*/
            read(p[0], &sum, sizeof(sum)); /*Read in the sum from the pipe input*/
            finalSum += sum;
        } else {perror("fork");abort();}
    } printf("I am the parent with process ID:%d with a final sum of %d.\n", (int)getpid(), finalSum);
    return 0;
}
