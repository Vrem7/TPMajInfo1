#include <unistd.h> // For write
#include <stdlib.h> // For exit
#include <string.h> // For strlen

#define WELCOME_MESSAGE "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT "enseash % "

void display(char * message){
    write(STDOUT_FILENO, message, strlen(message));
}

int main() {
    display(WELCOME_MESSAGE);
    while (1) {
        display(PROMPT);
        break;
    }
    return 0;
}