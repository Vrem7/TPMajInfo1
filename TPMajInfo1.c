#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h> // for open and close

#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT_FORMAT "enseash [%s:%d|%ldms] %% "
#define PROMPT "enseash % "
#define BUFFERSIZE 1024
#define EXIT_MESSAGE "Bye bye...\n"

// Function to display a message
void display(char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}

// Function to execute the entered command using fork and execlp
void executeCommand(char *command) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Parse the command to check for redirections
        char *token;
        char *inputFile = NULL;
        char *outputFile = NULL;

        token = strtok(command, " ");
        while (token != NULL) {
            if (strcmp(token, "<") == 0) {
                token = strtok(NULL, " ");
                inputFile = token;
            } else if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " ");
                outputFile = token;
            } else {
                token = strtok(NULL, " ");
            }
        }

        // Set up redirections if needed
        if (inputFile != NULL) {
            int fd = open(inputFile, O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (outputFile != NULL) {
            int fd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execlp(command, command, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        clock_gettime(CLOCK_MONOTONIC, &end);
        long duration = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;

        // Display the return code or signal and execution time in the prompt
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
        snprintf(prompt, sizeof(prompt), PROMPT_FORMAT, statusType, statusCode, duration);
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
