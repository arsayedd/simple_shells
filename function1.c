#include "shell.h"

/**
 * display - Prints a character string.
 * @ch: The character string.
 * @lent: The length of the string.
 * Return: Void.
 */
void display(char *ch, int lent)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, ch, lent);
}

/**
 * add_input - Takes command input.
 * @input: The command to use.
 * Return: The number of bytes read.
 */
ssize_t add_input(char *input)
{
	ssize_t red_bytes = read(STDIN_FILENO, input, INPUT_SIZE);

	return ((red_bytes == -1) ? -1
		: (red_bytes == 0) ? 0
		: (input[red_bytes] = '\0', red_bytes));
}

/**
 * exitShell - Exits the shell.
 * @status: The status code, if any.
 * Return: Void.
 */
void exitShell(int status)
{
	exit(status);
}

/**
 * chk_cmd_before_fork - Checks the command before creating a fork.
 * @user_command: The command to check.
 * Return: 0 for success and 1 otherwise.
 */
int chk_cmd_before_fork(char *user_command)
{
	char *path_lookup, *duplicate, *store_path;

	path_lookup = getenv("PATH");

	if (path_lookup == NULL)
		return (-1);

	duplicate = s_strdup(path_lookup);
	if (duplicate == NULL)
		return (-1);

	store_path = s_strtok(duplicate, ":");

	for (; store_path != NULL;)
	{
		char abs_path[PATH_SIZE];

		s_strcpy(abs_path, store_path);
		s_strcat(abs_path, "/");
		s_strcat(abs_path, user_command);

		if (access(abs_path, X_OK) == 0)
		{
			free(duplicate);
			return (0);
		}
		store_path = s_strtok(NULL, ":");
	}
	free(duplicate);
	return (1);
}

/**
 * signal_handler - Handles signals, particularly SIGINT.
 * @signal: The signal.
 * Return: Void.
 */
void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		display("$ ", s_strlen("$ "));
		fflush(stdout);
	}
}

