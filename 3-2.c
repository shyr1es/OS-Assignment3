/*
Each fork() invocation doubles the 
current number of processes because every existing process spawns a new one. 
Here is the breakdown:

Start: 1 process
First fork(): 2 processes
Second fork(): 4 processes
Third fork(): 8 processes
Therefore, a total of 8 processes are created, including the initial parent process.
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    /* fork a child process */
    fork();

    /* fork another child process */
    fork();

    /* and fork another */
    fork();

    return 0;
}
