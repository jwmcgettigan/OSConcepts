#include<stdio.h>
#include<stdlib.h>


int* test(int *n){

  printf("%d \n", *n);
}

int main(int argc,char* argv[])
{
  int n = 5;

  test(&n);

  exit(0);
}
