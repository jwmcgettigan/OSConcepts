#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int summation(int sum, int *num, int n) {
    for(int k = 0; k < n; k++){sum += num[k];}
    return sum;
}

int main(int argc, char *argv[]) {
    int i, p[2], sum, num[] = {2,3,7,-1,10,6}, a = atoi(argv[1]), n = (sizeof(num)/sizeof(*num));
    int r = n%a, s = 0, finalSum = 0;
    printf("I am the parent with process ID:%d.\n", (int)getpid());

    for (i = 0; i < n; i+=s) {
        pipe(p);
        if(r > 0){s = (n/a) + 1; r--;}
        else{s = n/a;}
        int slice[s];

        if (fork() == 0) { // child (new process)
            memcpy(slice, &num[i], s*sizeof(*num));
            sum = summation(0, slice, s);
            printf("I am the child with process ID:%d and my partial summation is: %d.\n", (int)getpid(), sum);
            close(p[0]); /*Closes up pipe input*/
            write(p[1], &sum, sizeof(sum)); /*Send the sum through the pipe output*/
            exit(0);
        } else { // parent goes down this path (main)
            close(p[1]); /*Closes up pipe output*/
            read(p[0], &sum, sizeof(sum)); /*Read in the sum from the pipe input*/
            finalSum += sum;
        }
    }
    printf("I am the parent with process ID:%d with a final sum of %d.\n", (int)getpid(), finalSum);
    return 0;
}

//int main(int argc, char *argv[]) {
//    int i, p[2], sum, num[] = {2,3,7,-1,10,6}, a = atoi(argv[1]), n = (sizeof(num)/sizeof(*num));
//    int r = n%a, s = 0, finalSum = 0;
//    //pipe(p);
//    printf("I am the parent with process ID:%d.\n", (int)getpid());
//
//    for (i = 0; i < n; i+=s) {
//        pipe(p);
//        if(r > 0){s = (n/a) + 1; r--;}
//        else{s = n/a;}
//        int slice[s];
//
//        //[2, 3][7,-1][10,6]
//        // 0  1  2  3  4  5
//
//        if (fork() == 0) { // child (new process)
//            //create_slice(num, s, slice);
//            memcpy(slice, &num[i], s*sizeof(*num));
//            sum = summation(0, slice, s);
//            printf("I am the child with process ID:%d and my partial summation is: %d.\n", (int)getpid(), sum);
//            close(p[0]); /*Closes up pipe input*/
//            write(p[1], &sum, sizeof(sum)); /*Send the sum through the pipe output*/
//            //close(p[1]);
//            exit(0);
//        } else { // parent goes down this path (main)
//            printf("i:%d\n", i);
//            close(p[1]); /*Closes up pipe output*/
//            read(p[0], &sum, sizeof(sum)); /*Read in the sum from the pipe input*/
//            printf("sum:%d\n", sum);
//            finalSum += sum;
//            printf("finalSum:%d\n", finalSum);
//            if (i == n-1)
//                printf("I am the parent with process ID:%d with a final sum of %d.\n", (int)getpid(), finalSum);
//            //close(p[0]);
//        }
//    }
//    return 0;
//}

//int main(int argc, char *argv[]) {
//    int i, p[2], sum, num[] = {2,3,7,-1,10,6}, a = atoi(argv[1]), n = (sizeof(num)/sizeof(*num));
//    int r = n%a, s = 0;
//    pipe(p);
//    printf("I am the parent with process ID:%d.\n", (int)getpid());
//
//    for (i = 0; i < n; i+=s) {
//        //printf("Before: n:%d | a:%d | s:%d | r:%d\n", n, a, s, r);
//        //r = n%a;
//        //printf("Mid: r:%d\n", r);
//        if(r > 0){s = (n/a) + 1; r--;}
//        else{s = n/a;}
//        //printf("After: n:%d | a:%d | s:%d | r:%d\n", n, a, s, r);
//        //printf("--------------------------------\n");
//        int slice[s];
//
//        if (fork() == 0) { // child (new process)
//            create_slice(num, s, slice);
//            sum = summation(0, slice, s);
//            printf("I am the child with process ID:%d and my partial summation is: %d.\n", (int)getpid(), sum);
//            close(p[0]); /*Closes up pipe input*/
//            write(p[1], &sum, sizeof(sum)); /*Send the sum through the pipe output*/
//            exit(0);
//        } else { // parent goes down this path (main)
//            printf("i:%d\n", i);
//            if (i == n - 1) {
//                close(p[1]); /*Closes up pipe output*/
//                read(p[0], &sum, sizeof(sum)); /*Read in the sum from the pipe input*/
//                printf("I am the parent with process ID:%d with a final sum of %d.\n", (int)getpid(), sum);
//            }
//        }
//    }
//    return 0;
//}

//int main(int argc, char *argv[]) {
//    int i, p[2], sum, num[] = {2,3,7,-1,10,6}, a = atoi(argv[1]), n = (sizeof(num)/sizeof(*num));
//    int r, s;
//    pipe(p);
//    printf("I am the parent with process ID:%d.\n", (int)getpid());
//
////    6 % 1 = 0 | 6 / 1 = 6
////    6 % 2 = 0 | 6 / 2 = 3
////    6 % 3 = 0 | 6 / 3 = 2
////    6 % 4 = 2 | 6 / 4 = 1
////    6 % 5 = 1 | 6 / 5 = 1
////    6 % 6 = 0 | 6 / 6 = 1
//
////    n % a = r | n / a = s
//
//    for (i = 0; i < a; i++) {
//        if (fork() == 0) {
//
//            r = n%a;
//            if(r > 0){s = (n/a) + 1; r--;}
//            else{s = n/a;}
//
//            int slice[s];
//            create_slice(num, s, slice);
//            sum = summation(0, slice, s);
//            printf("I am the child with process ID:%d and my partial summation is: %d.\n", (int)getpid(), sum);
//            exit(0);
//        }
//    }

//    for (i = 0; i < 2; i++){
//        if (fork() != 0) { // parent goes down this path (main)
//            close(p[1]); /*Closes up pipe output*/
//            read(p[0], &sum, sizeof(sum)); /*Read in the sum from the pipe input*/
//            printf("I am the parent with process ID:%d with a final sum of %d.\n", (int)getpid(), sum);
//        } else { // child (new process)
//            sum = summation(0, num, (sizeof(num)/sizeof(*num)));
//            printf("I am the child with process ID:%d and my partial summation is: %d.\n", (int)getpid(), sum);
//            close(p[0]); /*Closes up pipe input*/
//            write(p[1], &sum, sizeof(sum)); /*Send the sum through the pipe output*/
//            exit(0);
//        }
//    }
//    return 0;
//}

//-----------------------------------------------------------------

//int main(int argc, char *argv[]) {
//    int i, p[2], sum, num[] = {2,3,7,-1,10,6}, n = atoi(argv[1]);
//    int numLen = sizeof(num)/sizeof(*num);
//    double sliceSizeD = (numLen / (double)n);
//    int sliceSizeI = (numLen / (double)n) + 0.5;
//    double remainderD = numLen - n;
//    int remainderI = numLen % sliceSizeI;
//
//    printf("NumLen: %d\n", numLen);
//    printf("SliceSizeD: %f\n", sliceSizeD);
//    printf("SliceSizeI: %d\n", sliceSizeI);
//    printf("n: %d\n", n);
//    printf("RemainderD: %f\n", remainderD);
//    //printf("RemainderI: %d\n", remainderI);
//    pipe(p);
//    printf("I am the parent with process ID:%d.\n", (int)getpid());
//
//    for (i = 0; i < n; i++) {
//        if (fork() == 0) {
//            //int slice[] =
//            sum = summation(0, num, (sizeof(num)/sizeof(*num)));
//            exit(0);
//        }
//    }
//
//    for (i = 0; i < 2; i++){
//        if (fork() != 0) { // parent goes down this path (main)
//            close(p[1]); /*Closes up pipe output*/
//            read(p[0], &sum, sizeof(sum)); /*Read in the sum from the pipe input*/
//            printf("I am the parent with process ID:%d with a final sum of %d.\n", (int)getpid(), sum);
//        } else { // child (new process)
//            sum = summation(0, num, (sizeof(num)/sizeof(*num)));
//            printf("I am the child with process ID:%d and my partial summation is: %d.\n", (int)getpid(), sum);
//            close(p[0]); /*Closes up pipe input*/
//            write(p[1], &sum, sizeof(sum)); /*Send the sum through the pipe output*/
//            exit(0);
//        }
//    }
//    return 0;
//}
