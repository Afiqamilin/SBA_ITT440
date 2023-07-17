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
    int clientSocket;
    struct sockaddr_in serverAddress;
    int randomNumber;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address configuration
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Receive the random number from the server
    read(clientSocket, &randomNumber, sizeof(randomNumber));
    printf("Received random number from the server: %d\n", randomNumber);

    close(clientSocket);

    return 0;
}

