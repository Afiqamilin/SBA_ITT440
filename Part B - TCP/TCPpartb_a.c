#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main()
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressLength = sizeof(clientAddress);
    int randomNumber;

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address configuration
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Bind the socket to the specified IP address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 1) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is running and waiting for connections...\n");

    // Accept the connection from client
    newSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t *)&clientAddressLength);
    if (newSocket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Generate random number between 50,000 and 80,000
    randomNumber = rand() % 30001 + 50000;

    // Send the random number to the client
    write(newSocket, &randomNumber, sizeof(randomNumber));
    printf("Random number sent to the client: %d\n", randomNumber);

    close(newSocket);
    close(serverSocket);

    return 0;
}
	
