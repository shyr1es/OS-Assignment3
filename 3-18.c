/*
Using either a UNIX or a Linux system, write a C program that forks a child process that
ultimately becomes a zombie process. 
This zombie process must remain in the system for at least 10 seconds.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0);
    } else {
        printf("Parent process (PID: %d) created child (PID: %d).\n", getpid(), pid);
        printf("Check 'ps -l' to observe the zombie process.\n");
        sleep(10);
        printf("Parent process exiting.\n");
    }
    return 0;
}