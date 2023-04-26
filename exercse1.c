#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROMPT "#cisfun$ "

/**
 * main- check for unix
 *
 * unix: writting a command in unix
 * return: 0 if success
 */

int main(void)
{
    char command[1024];
    char *args[] = { NULL };
    int status;
    while (1) {
        // Display prompt
        printf(PROMPT);
        // Read user input
        if (fgets(command, sizeof(command), stdin) == NULL) {
            // Handle end-of-file condition
            printf("\n");
            break;
        }
        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';
        // Fork process to execute command
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process: execute command
            execve(command, args, NULL);
            // If execve returns, it means the command could not be executed
            printf("%s: command not found\n", command);
            exit(EXIT_FAILURE);
        } else {
            // Parent process: wait for child to finish
            wait(&status);
        }
    }

    return 0;
}

