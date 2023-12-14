#include "shell.h"

/**
 * tocen_command - function to tokenize command
 * @command: the user command
 * @args: array to store the command and arg
 * Return: the number of tokenize arg
 */
int tocen_command(char *command, char *args[])
{
	int index;
	char *copy = command;
	char *mytok = s_strtok(copy, TOK_DELIM);

	for (index = 0; mytok != NULL; index++)
	{
		args[index] = mytok;
		mytok = s_strtok(NULL, TOK_DELIM);
	}
	args[index] = NULL;

	return (index);
}
