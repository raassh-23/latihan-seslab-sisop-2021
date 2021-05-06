#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void *factorialThread(void *arg)
{
    int i;
    int x = *((int *)arg);
    int result = 1;

    for (int i = 2; i <= x; i++)
    {
        result *= i;
    }

    // this is dumb but it works
    usleep(x*1000);

    printf("%d! = %d\n", x, result);

    return NULL;
}

int main(int argc, char *argv[])
{
    int i;
    pthread_t tid[argc];
    int x[argc];

    for (i = 0; i < argc-1; i++)
    {
        x[i] = atoi(argv[i+1]);
        pthread_create(&(tid[i]), NULL, factorialThread, (void *)&(x[i]));
    }

    pthread_exit(NULL);

    return 0;
}