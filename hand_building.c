#include "main.h"

/**
 * hand_builtin - manages the builtin command
 * @first_sigment: pointer to first sigment of command
 * @arguments: pointer to array of arguments
 * Return: 0 if successful, otherwise 1
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int hand_builtin(char *first_sigment, char **arguments)
{

	if (_strcmp(first_sigment, "exit") == 0)
	{
		return (hand_exits(arguments));
	}
	else if (_strcmp(first_sigment, "cd") == 0)
	{
		return (hand_cd(arguments));
	}
	else if (_strcmp(first_sigment, "env") == 0)
	{
		free_args(arguments);
		return (hand_env(Environment));
	}
	else if (_strcmp(first_sigment, "setenv") == 0)
	{
		return (hand_setenv(arguments));
	}
	else if (_strcmp(first_sigment, "unsetenv") == 0)
	{
		return (hand_unsetenv(arguments));
	}
	else if (_strcmp(first_sigment, "alias") == 0)
	{
		return (hand_alias(arguments));
	}
	else if (_strcmp(first_sigment, "help") == 0)
	{
		free_args(arguments);
		print(STDOUT_FILENO, "RTFM: Read the fucking manual!\n", NULL);
		return (0);
	}
	else
	{
		return (0);
	}
}
/**
 * check_builtin - examines if the command is a builtin
 * @first_sigment: pointer to first segment of command
 * Return: 1 if builtin, otherwise 0
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int check_builtin(char *first_sigment)
{
	char *arr[] = {"exit", "cd", "env", "setenv", "unsetenv", "alias",
				   "help", NULL};
	int i;

	for (i = 0; arr[i]; i++)
	{
		if (_strcmp(first_sigment, arr[i]) == 0)
			return (1);
	}
	return (0);
}
