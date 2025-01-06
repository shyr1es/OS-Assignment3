#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

// Function to reverse the case of characters
void reverseCase(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        if (isupper(message[i])) {
            message[i] = tolower(message[i]);
        } else if (islower(message[i])) {
            message[i] = toupper(message[i]);
        }
    }
}

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create the first pipe
    if (pipe(pipe1) == -1) {
        perror("Pipe 1 creation failed");
        exit(EXIT_FAILURE);
    }

    // Create the second pipe
    if (pipe(pipe2) == -1) {
        perror("Pipe 2 creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(pipe1[1]); // Close write end of Pipe 1
        close(pipe2[0]); // Close read end of Pipe 2

        // Read the message from Pipe 1
        read(pipe1[0], buffer, BUFFER_SIZE);
        close(pipe1[0]); // Close read end of Pipe 1 after reading

        // Reverse the case of the message
        reverseCase(buffer);

        // Send the modified message to Pipe 2
        write(pipe2[1], buffer, strlen(buffer) + 1);
        close(pipe2[1]); // Close write end of Pipe 2 after writing

    } else {  // Parent process
        close(pipe1[0]); // Close read end of Pipe 1
        close(pipe2[1]); // Close write end of Pipe 2

        // Send a message to the child process
        printf("Enter a message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        write(pipe1[1], buffer, strlen(buffer) + 1);
        close(pipe1[1]); // Close write end of Pipe 1 after writing

        // Read the modified message from Pipe 2
        read(pipe2[0], buffer, BUFFER_SIZE);
        close(pipe2[0]); // Close read end of Pipe 2 after reading

        // Display the modified message
        printf("Modified message: %s\n", buffer);
    }

    return 0;
}
