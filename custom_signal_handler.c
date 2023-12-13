#include <signal.h>
#include <unistd.h>
#include "shell.h"

/**
 * custom_signal_handler - prints a new prompt upon a signal
 * @fildes: file descriptor
 *
 * Return: nothing
 */
void custom_signal_handler(int fildes)
{
    char *prompt = "\n($) ";

    (void)fildes;
    signal(SIGINT, custom_signal_handler);
    write(STDIN_FILENO, prompt, 5);
}
