#include "shell.h"

/**
 * execute_command - Creates a fork and executes a command.
 * @args: The command to execute.
 * @check: The number of tokens returned.
 * @status: The variable that keeps the value of the return.
 * @argv: The program name.
 * @envp: Parent environment.
 * Return: 0 for success.
 */
int execute_command(char *args[], int check, int *status, char *argv, char *envp[])
{
	int b;
	test mitest;
	pid_t child = fork();

	if (child < 0)
		return (-1);
	if (child == 0)
	{
		char **Args = malloc((check + 1) * sizeof(char *));

		if (Args == NULL)
			return (-1);
		for (b = 0; b < check; b++)
		{
			Args[b] = s_strdup(args[b]);

			if (Args[b] == NULL)
				return (-1);
		}
		Args[check] = NULL;

		if (call_up(Args[0], Args, argv, envp) == -1)
		{
			perror(Args[0]);
			exit(2);
		}
		for (b = 0; b < check; b++)
			free(Args[b]);
		free(Args);
	}

	else
	{
		wait(&(mitest.status));
		if (WIFEXITED(mitest.status))
			mitest.status = WEXITSTATUS(mitest.status);
		*status = mitest.status;
	}
	return (mitest.status);
}

