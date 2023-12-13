#include "shell.h"

/**
 * custom_readline_error - User input reading error
 *
 * Return: nothing
 */
void custom_readline_error(void)
{
    char *err = strcat(strcat(name, ": "), CUSTOM_READLINE_ERROR);

    write(2, err, strlen(err));
    exit(EXIT_FAILURE);
}

