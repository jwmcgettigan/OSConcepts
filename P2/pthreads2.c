#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* the thread */
int fibonacci(int x);

int main(int argc, char *argv[])
{
	int count, i;

	if (argc != 2) {
		fprintf(stderr,"usage: pthreads <integer value>\n");
		return -1;
	}

	count = atoi(argv[1]);

	if (count < 1) {
		fprintf(stderr,"%d must be>= 1\n", count);
		return -1;
	}

	pthread_t thread[count];
	for(i=0;i<count;i++){
		pthread_create(&thread[i],NULL,runner,(void*)(intptr_t)i);
	}

	for(i=0;i<count;i++){
		pthread_join(thread[i],NULL);
	}
  printf("\n");

  return 0;
}

void *runner(void *param)
{
	printf("%d ", fibonacci((int)(intptr_t)param));
	pthread_exit(0);
}

int fibonacci (int x)
{
    if (x <= 1)
        return x;
    return fibonacci(x-1) + fibonacci(x-2);
}
