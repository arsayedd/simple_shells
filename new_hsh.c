#include "new_shell.h"

/**
 * new_hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int new_hsh(new_info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_new_info(info);
        if (new_interactive(info))
            new_puts("$ ");
        new_eputchar(NEW_BUF_FLUSH);
        r = get_new_input(info);
        if (r != -1)
        {
            set_new_info(info, av);
            builtin_ret = find_new_builtin(info);
            if (builtin_ret == -1)
                find_new_cmd(info);
        }
        else if (new_interactive(info))
            new_putchar('\n');
        free_new_info(info, 0);
    }
    write_new_history(info);
    free_new_info(info, 1);
    if (!new_interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}

/**
 * find_new_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *          -2 if builtin signals exit()
 */
int find_new_builtin(new_info_t *info)
{
    int i, built_in_ret = -1;
    new_builtin_table builtintbl[] = {
        {"exit", new_myexit},
        {"env", new_myenv},
        {"help", new_myhelp},
        {"history", new_myhistory},
        {"setenv", new_mysetenv},
        {"unsetenv", new_myunsetenv},
        {"cd", new_mycd},
        {"alias", new_myalias},
        {NULL, NULL}};

    for (i = 0; builtintbl[i].type; i++)
        if (new_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return (built_in_ret);
}

/**
 * find_new_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_new_cmd(new_info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!new_is_new_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_new_path(info, new_getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        new_fork_cmd(info);
    }
    else
    {
        if ((new_interactive(info) || new_getenv(info, "PATH=") || info->argv[0][0] == '/') && is_new_cmd(info, info->argv[0]))
            new_fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_new_error(info, "not found\n");
        }
    }
}

/**
 * new_fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void new_fork_cmd(new_info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_new_environ(info)) == -1)
        {
            free_new_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_new_error(info, "Permission denied\n");
        }
    }
}
