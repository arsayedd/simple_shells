#include "my_shell.h"

/**
 * main - Simple Shell 0.1
 *
 * Return: Always 0.
 */
int main(void)
{
    char *input;

    while (1)
    {
        write_prompt();
        input = read_line();

        if (!input)
        {
            _eputs("\n");
            break;
        }

        if (_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }

        execute_command(input);
        free(input);
    }

    return (0);
}
