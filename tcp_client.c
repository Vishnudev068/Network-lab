#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int client_socket, port;
    struct sockaddr_in server_addr;
    socklen_t len;
    int a, b, sum;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set server address structure
    len = sizeof(server_addr);
    bzero((char*)&server_addr, sizeof(server_addr));

    printf("Enter the port number: ");
    scanf("%d", &port);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Trying to connect to the server...\n");

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to the server!\n");

    // Get input numbers from the user
    printf("Enter two numbers for addition: ");
    scanf("%d %d", &a, &b);

    // Send numbers to the server
    send(client_socket, &a, sizeof(a), 0);
    send(client_socket, &b, sizeof(b), 0);

    printf("Receiving sum from server...\n");

    // Receive sum from server
    recv(client_socket, &sum, sizeof(sum), 0);

    printf("Sum received: %d\n", sum);

    // Close socket
    close(client_socket);

    return 0;
}
