#include "shell.h"

/**
 * getEnvironmentVariableValue - Get the value of an environment variable.
 * @varName: The variable name.
 * @envp: The parent environment.
 * Return: The environment variable value.
 */
char *getEnvironmentVariableValue(char *varName, char *envp[])
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		char *envEntry = envp[i];

		if (s_strstr(envEntry, varName) == envEntry)
		{
			const char *equals = s_strchr(envEntry, '=');

			if (equals != NULL)
			{
				return (s_strdup(equals + 1));
			}
		}
	}
	return (NULL);
}

/**
 * handleDoubleDollarInternal - Handle $$ substitution.
 * @cmd: The command.
 * @output: The output.
 * @i: Counter.
 * @j: Counter.
 * Return: void
 */
void handleDoubleDollarInternal(char __attribute__((__unused__)) *cmd, char *output, int *i, int *j)
{
	char *pidStr = getProcessIdString();
	int k = 0;

	while (pidStr[k] != '\0')
	{
		output[(*j)++] = pidStr[k++];
	}
	free(pidStr);
	(*i) += 2;
}

/**
 * handleEnvironmentVariable - Handle environment variable substitution.
 * @cmd: The command.
 * @output: The output result.
 * @i: Counter.
 * @j: Counter.
 * @envp: Parent environment.
 * Return: void
 */
void handleEnvironmentVariable(char *cmd, char *output, int *i, int *j, char *envp[])
{
	int k = (*i);

	while (s_isalnum((unsigned char)cmd[(*i)]) || cmd[(*i)] == '_')
	{
		(*i)++;
	}

	if (k != (*i))
	{
		char *envVar = s_strndup(&cmd[k], (*i) - k);
		char *envValue = getEnvironmentVariableValue(envVar, envp);

		if (envValue)
		{
			int l = 0;

			while (envValue[l] != '\0')
			{
				output[(*j)++] = envValue[l++];
			}
			free(envValue);
		}
		free(envVar);
	}
	else
	{
		output[(*j)++] = '$';
	}
}

/**
 * handleDoubleDollars - Handle environment variable substitution in the command.
 * @cmd: The command.
 * @envp: Parent environment.
 * Return: The absolute variable.
 */
char *handleDoubleDollars(char *cmd, char *envp[])
{
	char *output = malloc(strlen(cmd) * 10 + 1);
	int i = 0, j = 0;

	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$' && cmd[i + 1] == '$')
		{
			handleDoubleDollarInternal(cmd, output, &i, &j);
		}
		else if (cmd[i] == '$')
		{
			i++;
			handleEnvironmentVariable(cmd, output, &i, &j, envp);
		}
		else
		{
			output[j++] = cmd[i++];
		}
	}

	output[j] = '\0';
	return (output);
}

/**
 * getProcessIdString - Get the process id as a string.
 * Return: The process id as a string.
 */
char *getProcessIdString()
{
	pid_t pid = getpid();
	char pidBuff[16];
	int i = 0;
	char *pidStr;

	if (pid == 0)
	{
		pidBuff[i++] = '0';
	}
	else
	{
		while (pid > 0)
		{
			pidBuff[i++] = '0' + (pid % 10);
			pid /= 10;
		}
	}

	pidStr = malloc(i + 1);
	if (pidStr)
	{
		int j = 0;
		int k;

		for (k = i - 1; k >= 0; k--)
		{
			pidStr[j++] = pidBuff[k];
		}

		pidStr[j] = '\0';
	}

	return (pidStr);
}

