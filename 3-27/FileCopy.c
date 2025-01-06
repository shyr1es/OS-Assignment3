#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int pipe_fd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(pipe_fd[1]); // Close the write end of the pipe

        // Open the destination file for writing
        int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (dest_fd < 0) {
            perror("Failed to open destination file");
            exit(EXIT_FAILURE);
        }

        // Read from the pipe and write to the destination file
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE)) > 0) {
            if (write(dest_fd, buffer, bytes_read) != bytes_read) {
                perror("Write to destination file failed");
                close(dest_fd);
                exit(EXIT_FAILURE);
            }
        }
        if (bytes_read < 0) {
            perror("Read from pipe failed");
        }

        close(dest_fd);   // Close the destination file
        close(pipe_fd[0]); // Close the read end of the pipe
    } else {  // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe

        // Open the source file for reading
        int src_fd = open(argv[1], O_RDONLY);
        if (src_fd < 0) {
            perror("Failed to open source file");
            exit(EXIT_FAILURE);
        }

        // Read from the source file and write to the pipe
        ssize_t bytes_read;
        while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
            if (write(pipe_fd[1], buffer, bytes_read) != bytes_read) {
                perror("Write to pipe failed");
                close(src_fd);
                exit(EXIT_FAILURE);
            }
        }
        if (bytes_read < 0) {
            perror("Read from source file failed");
        }

        close(src_fd);    // Close the source file
        close(pipe_fd[1]); // Close the write end of the pipe

        // Wait for the child process to complete
        wait(NULL);
    }

    return 0;
}
