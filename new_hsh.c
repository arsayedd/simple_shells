#include "new_shell.h"

/**
 * `new_hsh` is the central loop of the innovative shell.
 * This function handles user input, processes built-in commands,
 * and executes external commands when found in the PATH.
 *
 * @param info The information and configuration structure.
 * @param av   The argument vector from the main program.
 * @return     Returns 0 on success, 1 on error, or an error code.
 */
int new_hsh(new_info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    // Main shell loop for user interaction
    while (r != -1 && builtin_ret != -2)
    {
        clear_new_info(info);

        // Display prompt for interactive sessions
        if (new_interactive(info))
            new_puts("$ ");

        new_eputchar(NEW_BUF_FLUSH);
        r = get_new_input(info);

        // Process user input and execute commands
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

    // Cleanup and exit
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
 * `find_new_builtin` searches for a built-in command in the new shell.
 * If the command is found, it executes the corresponding function.
 *
 * @param info The information and configuration structure.
 * @return     Returns -1 if the built-in is not found,
 *             0 if the built-in is executed successfully,
 *             1 if the built-in is found but not successful,
 *             -2 if the built-in signals an exit().
 */
int find_new_builtin(new_info_t *info)
{
    int i, built_in_ret = -1;

    // Built-in commands and their corresponding functions
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

    // Iterate through built-in commands to find a match
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
 * `find_new_cmd` locates and executes external commands found in the PATH.
 * If the command is not found, it prints an error message.
 *
 * @param info The information and configuration structure.
 * @return     Void.
 */
void find_new_cmd(new_info_t *info)
{
    char *path = NULL;
    int i, k;

    // Set the initial path to the command
    info->path = info->argv[0];

    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }

    // Count non-delimiter arguments
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!new_is_new_delim(info->arg[i], " \t\n"))
            k++;

    // If no arguments, return
    if (!k)
        return;

    // Find the command in the PATH
    path = find_new_path(info, new_getenv(info, "PATH="), info->argv[0]);

    // Execute the command if found
    if (path)
    {
        info->path = path;
        new_fork_cmd(info);
    }
    else
    {
        // Print an error if the command is not found
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
 * `new_fork_cmd` forks a new process to execute an external command.
 * It handles the child and parent processes, waiting for the child to finish.
 *
 * @param info The information and configuration structure.
 * @return     Void.
 */
void new_fork_cmd(new_info_t *info)
{
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1)
    {
        // Handle fork error
        perror("Error:");
        return;
    }

    if (child_pid == 0)
    {
        // Child process: execute the command
        if (execve(info->path, info->argv, get_new_environ(info)) == -1)
        {
            // Handle execve error
            free_new_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        // Parent process: wait for the child to finish
        wait(&(info->status));

        // Check the exit status of the child
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);

            // Print error message for permission denied
            if (info->status == 126)
                print_new_error(info, "Permission denied\n");
        }
    }
}
