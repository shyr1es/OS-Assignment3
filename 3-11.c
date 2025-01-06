/*
The number of processes doubles with each fork():

Start: 1 process

First fork(): 2 processes

Second fork(): 4 processes

Third fork(): 8 processes

Fourth fork(): 16 processes

Total processes, including the parent: 16.
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    int i;

    for (i = 0; i < 4; i++)
        fork();

    return 0;
}
