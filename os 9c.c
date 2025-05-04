#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void)
{
    int pid;
    int status;
    printf("Hello World!\n");
    pid = fork();
    if (pid == -1)
    {
        perror("bad fork");
        exit(1);
    }
    if (pid == 0)
    {
        printf("I am the child process.\n");
    }
    else
    {
        wait(&status);
        printf("I am the parent process.\n");
    }
    return 0;
}
