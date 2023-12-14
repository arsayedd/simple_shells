#include "shell.h"

/**
 * s_getenv - Get environment variable value.
 * @string: The environment variable to retrieve.
 * @envp: Parent environment.
 * Return: Pointer to the string result.
 */
char *s_getenv(const char *string, char *envp[])
{
	int index = 0;

	while (envp[index] != NULL)
	{
		char *start = envp[index];

		if (s_strncmp(start, string, s_strlen(string)) == 0
			&& start[s_strlen(string)] == '=')
		{
			return (start + s_strlen(string) + 1);
		}
		index++;
	}
	return (NULL);
}

/**
 * sep_cmd - Separate command into an array.
 * @user_command: The user command.
 * @result: The array where the separated command will be stored.
 * @num: Maximum number of commands.
 * Return: The number of separated commands.
 */
int sep_cmd(const char *user_command, char *result[], int num)
{
	int index = 0;
	char *duplicate = s_strdup(user_command);
	char *token = s_strtok(duplicate, ";");

	while (token != NULL && index < num)
	{
		result[index] = token;
		token = s_strtok(NULL, ";");
		index++;
	}

	free(duplicate);
	return (index);
}

/**
 * replace_status_variable - Replace status variable in command.
 * @args: The command.
 * @count: Number of commands being executed.
 * @last_status: Variable to hold the status code.
 * Return: Void.
 */
void replace_status_variable(char *args[], int count, int *last_status)
{
	int index;

	for (index = 0; index < count; index++)
	{
		if (s_strcmp(args[index], "$?") == 0)
		{
			char last_status_str[12];

			intToString(*last_status, last_status_str, sizeof(last_status_str));
			args[index] = s_strdup(last_status_str);
		}
	}
}

/**
 * intToString - Convert int to string.
 * @num: The number to convert.
 * @str: The string to convert to.
 * @str_size: The size of the string.
 * Return: Void.
 */
void intToString(int num, char *str, int str_size)
{
	int temp = num;
	int numDigits = 1;

	while (temp / 10 != 0)
	{
		numDigits++;
		temp /= 10;
	}
	if (str_size <= numDigits)
	{
		return;
	}
	str[numDigits] = '\0';

	while (numDigits > 0)
	{
		numDigits--;
		str[numDigits] = '0' + (num % 10);
		num /= 10;
	}
}

