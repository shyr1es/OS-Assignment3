#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6017
#define BUFFER_SIZE 512

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char *quote = "The only limit to our realization of tomorrow is our doubts of today.\n";

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Quote of the Day server is running on port %d...\n", PORT);

    // Accept and handle connections
    socklen_t addr_len = sizeof(client_addr);
    while ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) >= 0) {
        printf("Client connected...\n");

        // Send the quote to the client
        send(client_fd, quote, strlen(quote), 0);

        // Close the connection
        close(client_fd);
        printf("Quote sent. Connection closed.\n");
    }

    // Clean up
    close(server_fd);
    return 0;
}
