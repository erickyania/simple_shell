#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

/**
 * main: start  execution
 *
 * unix: unix command interpreter
 * return: 0 on sucess
 */


int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[] = { NULL };
    pid_t pid;
    int status;

    while (1) {
        // Display prompt and read user input
        printf("$ ");
        if (!fgets(command, MAX_COMMAND_LENGTH, stdin)) {
            // Handle end-of-file condition
            break;
        }

        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Fork process to execute command
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process: execute command
            execve(command, args, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process: wait for child to finish
            do {
                if (waitpid(pid, &status, WUNTRACED) == -1) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return 0;
}

