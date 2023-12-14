#include "main.h"

/**
* gets_path - Retrieves the PATH variable from the environment
* @envp: Pointer to environment
* Return: Pointer to the PATH variable
* Description: This function is not portable and will only work on Linux.
* by Ahmed Raafat & Ahmed Abdelnasser
*/

char *gets_path(char *envp[])
{
char *path = "PATH=";
char cur_env[BUFFER_SIZE];
int i = 0;

while (envp[i])
{
_memecopy(cur_env, envp[i], _strllen(path));
cur_env[_strllen(path)] = '\0';
if (_strccmp(path, cur_env) == 0)
{
return (envp[i] + _strllen(path));
}
i++;
}
return (NULL);
}

/**
* find_paths - Finds the path to a command
* @path_i: Path to search
* @input: Command to search for in the PATH variable (e.g., ls)
* Return: Pointer to the path if found, otherwise NULL
* by Ahmed Raafat & Ahmed Abdelnasser
*/

char *find_paths(char *path_i, char *input)
{
char *path, *chank = NULL;

if (path_i)
{
path = _strdup(path_i);
chank = _strtok(path, ":");
}
else
{
return (NULL);
}
while (chank != NULL && *path_i)
{
size_t buffer_size = _strllen(chank) + 1 + _strllen(input) + 1;
char *buffer = _malloc(buffer_size);
int i = 0, j = 0, x = 0;

while (chank[j])
{
buffer[i] = chank[j];
i++, j++;
}
buffer[i] = '/';
i++;
while (input[x])
{
buffer[i] = input[x];
i++, x++;
}
buffer[i] = '\0';
if (access(buffer, X_OK) == 0)
{
free(path);
return (buffer);
}
free(buffer);
chank = _strtok(NULL, ":");
}
free(path);
return (NULL);
}
