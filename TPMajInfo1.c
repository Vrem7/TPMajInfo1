#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT_FORMAT "enseash [%s:%d] %% "
#define PROMPT "enseash % "
#define BUFFERSIZE 1024
#define EXIT_MESSAGE "Bye bye...\n"

// Function to display a message
void display(char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}

// Function to execute the entered command using fork and execlp
void executeCommand(char *command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execlp(command, command, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        // Display the return code or signal in the prompt
        char statusType[8];
        int statusCode;

        if (WIFEXITED(status)) {
            // If the child process terminated normally
            strcpy(statusType, "exit");
            statusCode = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            // If the child process terminated due to a signal
            strcpy(statusType, "sign");
            statusCode = WTERMSIG(status);
        }

        char prompt[BUFFERSIZE];
        snprintf(prompt, sizeof(prompt), PROMPT_FORMAT, statusType, statusCode);
        display(prompt);
    }
}

int main() {
    display(WELCOME_MESSAGE);
    display(PROMPT);

    while (1) {
        char input[BUFFERSIZE];

        // Read the command entered by the user
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Waiting for exit
        if (strcmp(input, "exit") == 0) {
            display(EXIT_MESSAGE);
            break;
        }

        // Execute the entered command
        executeCommand(input);
    }

    return 0;
}
