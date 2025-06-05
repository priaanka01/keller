#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from Parent!";
    char read_msg[50];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        close(fd[1]);
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);
    } else {
        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
-----------------------------------------------------------------------------------------------------
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
