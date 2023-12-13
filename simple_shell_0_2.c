#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    char *cmd;
    size_t bufsize = 1024;
    ssize_t characters;

    while (1) {
        printf("#cisfun$ ");
        cmd = NULL;
        characters = getline(&cmd, &bufsize, stdin);

        if (characters == -1) {
            // Handle end of file condition
            printf("\n");
            free(cmd);
            break;
        }

        // Remove the newline character at the end
        cmd[characters - 1] = '\0';

        // Tokenize the command line to separate command and arguments
        char *token = strtok(cmd, " ");
        
        // Execute the command using execve with arguments
        if (execve(token, &token, NULL) == -1) {
            // Handle errors here
            perror("./shell");
        }

        free(cmd);
    }

    return 0;
}

