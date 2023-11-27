#include <unistd.h> // For write
#include <stdlib.h> // For exit
#include <string.h> // For strlen
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT "enseash % "
#define BUFFERSIZE 1024

// Function to display a message
void display(char * message){
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
    }
}


int main() {
    display(WELCOME_MESSAGE);
    while (1) {
        display(PROMPT);
        char input[BUFFERSIZE];
        
        // Read the command entered by the user
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Execute the entered command
        executeCommand(input);
    }
    return 0;
}

