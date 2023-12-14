#include "shell.h"

/**
 * changeDirectory - Change the current working directory.
 * @path: The path to the directory to change to.
 * @programName: The program name.
 * Return: 0 for success, 1 for failure.
 */
int changeDirectory(const char *path, char *programName)
{
	if (chdir(path) != 0)
	{
		const char *errMsg = ": 1: cd: can't cd to ";

		write(2, programName, s_strlen(programName));
		write(2, errMsg, s_strlen(errMsg));
		write(2, path, s_strlen(path));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

/**
 * updateEnvVariables - Update environment variables after cd.
 * @newPath: The new current working directory path.
 * @envp: Parent environment.
 * Return: 0 for success, 1 for failure.
 */
int updateEnvVariables(const char *newPath, char *envp[])
{
	if (setenv("OLDPWD", s_getenv("PWD", envp), 1) != 0 || setenv("PWD", newPath, 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	return (0);
}

/**
 * cdCommand - Implement the cd command.
 * @args: The argument for cd.
 * @programName: The program name.
 * @envp: Parent environment.
 * Return: 0 for success, 1 otherwise.
 */
int cdCommand(const char *args, char *programName, char *envp[])
{
	char cwd[PATH_SIZE];

	if (args == NULL || args[0] == '\0')
	{
		const char *home = s_getenv("HOME", envp);

		if (home == NULL)
		{
			perror("cd");
			return (1);
		}
		args = home;
	}
	else if (s_strcmp(args, "-") == 0)
	{
		const char *prev = s_getenv("OLDPWD", envp);

		if (prev == NULL)
		{
			perror("cd");
			return (1);
		}
		args = prev;
		write(1, "\n", 1);
		write(1, prev, s_strlen(prev));
	}

	if (changeDirectory(args, programName) != 0)
		return (1);

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, s_strlen(cwd));
		write(1, "\n", 1);
	}

	if (updateEnvVariables(args, envp) != 0)
		return (1);

	return (0);
}
