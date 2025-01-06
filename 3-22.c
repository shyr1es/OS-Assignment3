/*
 Modify the program in Exercise 3.21 to use shared memory for storing the Collatz sequence.

This version stores the Collatz sequence in a shared memory object:

Steps:

The parent creates a shared memory segment.

The child writes the sequence to shared memory.

The parent reads and prints the sequence after the child completes.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>

void collatz(int n, char *buffer) {
    char temp[50];
    while (n != 1) {
        sprintf(temp, "%d ", n);
        strcat(buffer, temp);
        if (n % 2 == 0)
            n /= 2;
        else
            n = 3 * n + 1;
    }
    strcat(buffer, "1\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Error: Enter a positive integer.\n");
        exit(1);
    }

    char *shared_memory = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        collatz(n, shared_memory);
        exit(0);
    } else {
        wait(NULL);
        printf("Parent process: Collatz sequence from shared memory:\n%s", shared_memory);
    }
