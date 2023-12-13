#include "new_shell.h"

/**
 * Determines if a file is an executable command.
 *
 * @param info The info struct.
 * @param path Path to the file.
 * @return 1 if true, 0 otherwise.
 */
int is_new_cmd(new_info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * Duplicates characters from a given path string within a specified range.
 *
 * @param pathstr The PATH string.
 * @param start   Starting index.
 * @param stop    Stopping index.
 * @return        Pointer to the new buffer.
 */
char *new_dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = 0;
    return (buf);
}

/**
 * Finds the full path of a command in the PATH string.
 *
 * @param info    The info struct.
 * @param pathstr The PATH string.
 * @param cmd     The command to find.
 * @return        Full path of the command if found, or NULL.
 */
char *find_new_path(new_info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);
    if ((new_strlen(cmd) > 2) && new_starts_with(cmd, "./"))
    {
        if (is_new_cmd(info, cmd))
            return (cmd);
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = new_dup_chars(pathstr, curr_pos, i);
            if (!*path)
                new_strcat(path, cmd);
            else
            {
                new_strcat(path, "/");
                new_strcat(path, cmd);
            }
            if (is_new_cmd(info, path))
                return (path);
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}
