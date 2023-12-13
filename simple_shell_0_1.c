#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

        // Execute the command using execve
        if (execve(cmd, NULL, NULL) == -1) {
            // Handle errors here
            perror("./shell");
        }

        free(cmd);
    }

    return 0;
}

