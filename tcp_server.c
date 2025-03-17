#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_socket, client_socket, port;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;
    int a, b, sum;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Zero out the server_addr structure
    bzero((char*)&server_addr, sizeof(server_addr));

    // Set server address structure
    server_addr.sin_family = AF_INET;
    printf("Enter the port number: ");
    scanf("%d", &port);
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // Listen for client connections
    listen(server_socket, 5);
    printf("Waiting for client connection...\n");

    len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &len);
    if (client_socket < 0) {
        perror("Accept failed");
        exit(1);
    }

    printf("Client connected!\n");

    // Read numbers from the client
    read(client_socket, &a, sizeof(a));
    read(client_socket, &b, sizeof(b));

    printf("The client has sent %d and %d\n", a, b);

    // Calculate sum
    sum = a + b;
    printf("Sum is %d\n", sum);

    // Send sum back to the client
    write(client_socket, &sum, sizeof(sum));

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
