/*
 Write a C program using the fork() system call that generates the Collatz sequence in the child process.

The Collatz sequence for a positive integer n follows these rules:

If n is even, divide it by 2.

If n is odd, multiply it by 3 and add 1.

The program will:

Accept the starting number as a command-line argument.

Use fork() to create a child process that computes and prints the sequence.

The parent process waits for the child to complete.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void collatz(int n) {
    while (n != 1) {
        printf("%d ", n);
        if (n % 2 == 0)
            n /= 2;
        else
            n = 3 * n + 1;
    }
    printf("1\n");
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

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child process: Collatz sequence starting from %d\n", n);
        collatz(n);
        exit(0);
    } else {
        wait(NULL);
        printf("Parent process: Child process completed.\n");
    }

    return 0;
}