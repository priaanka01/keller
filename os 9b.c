#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
int global = 10; 
int main() 
{ 
    int local = 20; 
    pid_t pid; 
    printf("before fork\n"); 
    printf("pid=%d,global=%d,local=%d\n", getpid(), global, local); 
    pid = fork(); 
    if (pid < 0) 
        printf("failed to create child"); 
    else if (pid == 0) 
    { 
        printf("after fork\n"); 
        global++; 
        local++; 
    } 
    else if (pid > 0) 
        sleep(2); 
    printf("cid=%d,global=%d,local=%d\n", getpid(), global, local); 
    exit(0); 
}
