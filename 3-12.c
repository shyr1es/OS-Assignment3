/*
 Explain the circumstances under which the line of code marked printf("LINE J") in Figure 3.22 will be reached.

The printf("LINE J") line will execute only if the execlp() function call fails. 
This could occur if the specified program is not found or cannot be executed. When execlp() fails, 
the process continues executing subsequent lines of code.
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    /* fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* child process */
        execlp("/bin/ls", "ls", NULL);
        printf("LINE J");
    }
    else { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf("Child Complete");
    }

    return 0;
}
