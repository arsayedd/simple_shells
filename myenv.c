#include "new_shell.h"

/**
 * new_myenv - Prints the current environment.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int new_myenv(new_info_t *info)
{
    new_print_list_str(info->env);
    return (0);
}

/**
 * new_getenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the variable or NULL if not found.
 */
char *new_getenv(new_info_t *info, const char *name)
{
    new_list_t *node = info->env;
    char *p;

    while (node)
    {
        p = new_starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * new_mysetenv - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int new_mysetenv(new_info_t *info)
{
    if (info->argc != 3)
    {
        new_eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (new_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * new_myunsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int new_myunsetenv(new_info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        new_eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        new_unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * new_populate_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int new_populate_env_list(new_info_t *info)
{
    new_list_t *node = NULL;
    size_t i;

    for (i = 0; new_environ[i]; i++)
        new_add_node_end(&node, new_environ[i], 0);
    info->env = node;
    return (0);
}
