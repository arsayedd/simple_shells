#include "new_shell.h"

/**
 * Determines if the current character in the buffer is a chain delimiter.
 *
 * @param info The parameter struct.
 * @param buf The character buffer.
 * @param p   Address of the current position in buf.
 * @return    1 if a chain delimiter is found, 0 otherwise.
 */
int is_new_chain(new_info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = NEW_CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = NEW_CMD_AND;
    }
    else if (buf[j] == ';') /* Found end of this command */
    {
        buf[j] = 0; /* Replace semicolon with null */
        info->cmd_buf_type = NEW_CMD_CHAIN;
    }
    else
        return (0);

    *p = j;
    return (1);
}

/**
 * Checks whether to continue chaining based on the last status.
 *
 * @param info The parameter struct.
 * @param buf  The character buffer.
 * @param p    Address of the current position in buf.
 * @param i    Starting position in buf.
 * @param len  Length of buf.
 * @return     Void.
 */
void check_new_chain(new_info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == NEW_CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    if (info->cmd_buf_type == NEW_CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * Replaces aliases in the tokenized string.
 *
 * @param info The parameter struct.
 * @return     1 if replaced, 0 otherwise.
 */
int replace_new_alias(new_info_t *info)
{
    int i;
    new_list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = new_node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);

        new_free(info->argv[0]);
        p = new_strchr(node->str, '=');

        if (!p)
            return (0);

        p = new_strdup(p + 1);

        if (!p)
            return (0);

        info->argv[0] = p;
    }

    return (1);
}

/**
 * Replaces variables in the tokenized string.
 *
 * @param info The parameter struct.
 * @return     1 if replaced, 0 otherwise.
 */
int replace_new_vars(new_info_t *info)
{
    int i = 0;
    new_list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!new_strcmp(info->argv[i], "$?"))
        {
            replace_new_string(&(info->argv[i]), new_strdup(convert_number(info->status, 10, 0)));
            continue;
        }

        if (!new_strcmp(info->argv[i], "$$"))
        {
            replace_new_string(&(info->argv[i]), new_strdup(convert_number(getpid(), 10, 0)));
            continue;
        }

        node = new_node_starts_with(info->env, &info->argv[i][1], '=');

        if (node)
        {
            replace_new_string(&(info->argv[i]), new_strdup(new_strchr(node->str, '=') + 1));
            continue;
        }

        replace_new_string(&info->argv[i], new_strdup(""));
    }

    return (0);
}

/**
 * Replaces a string.
 *
 * @param old Address of the old string.
 * @param new New string.
 * @return    1 if replaced, 0 otherwise.
 */
int replace_new_string(char **old, char *new)
{
    new_free(*old);
    *old = new;
    return (1);
}

