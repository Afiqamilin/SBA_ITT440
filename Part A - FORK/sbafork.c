#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MESSAGE_SIZE 100

int main()
{
    int childCount = 3;
    pid_t pid[childCount];
    int fd[childCount][2];  // File descriptors for pipes

    // Create pipes
    for (int i = 0; i < childCount; i++) {
        if (pipe(fd[i]) == -1) {
            perror("Pipe creation failed");
            return 1;
        }
    }

    // Create child processes
    for (int i = 0; i < childCount; i++) {
        pid[i] = fork();

        if (pid[i] < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid[i] == 0) {
            // Child process
            close(fd[i][1]);  // Close the write end of the pipe

            char message[MESSAGE_SIZE];
            read(fd[i][0], message, sizeof(message));
            printf("Child %d received message: %s\n", getpid(), message);

            close(fd[i][0]);  // Close the read end of the pipe
            exit(0);
        } else {
            // Parent process
            close(fd[i][0]);  // Close the read end of the pipe

            char message[MESSAGE_SIZE];
            sprintf(message, "Message from parent to child %d", pid[i]);

            write(fd[i][1], message, strlen(message) + 1);
            close(fd[i][1]);  // Close the write end of the pipe
        }
    }

    // Parent process waits for child processes to finish
    for (int i = 0; i < childCount; i++) {
        wait(NULL);
    }

    return 0;
}

