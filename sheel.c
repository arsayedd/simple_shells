#include "shell.h"

/**
 * main - Entry point for the main function
 * @argc: The number of arguments
 * @argv: Array to store the arguments
 * @envp: The parent environment
 * Return: 0 for success, 1 otherwise
 */
int main(int argc, char *argv[], char *envp[])
{
	display("$ ", s_strlen("$ "));
	input = add_input(command);
	if (input == -1)
		continue;
	else if (input == 0)
	{
		display("\n", s_strlen("\n"));
		break;
	}

	disable_comment(command);
	cmd = handle_double_dollars(command, envp);
	status = run_command(cmd, argv[0], envp);

	free(cmd);

	return (status);
}
