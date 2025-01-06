/*The fork() system call generates a child process with a separate memory space. 
Any changes made to the value variable in the child process do not influence 
the parent process since they operate in independent memory contexts. 
In the parent process, value retains its original value of 5. 
Consequently, at LINE A, the following will be printed:
PARENT: value = 5
*/ 
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int value = 5;

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0) { /* child process */
        value += 15;
        return 0;
    }
    else if (pid > 0) { /* parent process */
        wait(NULL);
        printf("PARENT: value = %d", value); /* LINE A */
        return 0;
    }
} 


