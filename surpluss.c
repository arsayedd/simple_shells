#include "shell.h"

/**
 * is_whitespace - Check for whitespace
 * @c: The character to check
 * Return: Escape character
 */
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * is_word_start - Check if a word starts
 * @str: The string to search
 * @index: The index to iterate over
 * Return: 1 if success
 */
int is_word_start(char *str, int index)
{
    if (index == 0 || is_whitespace(str[index - 1]))
    {
        return 1;
    }
    return 0;
}

/**
 * check_cmd - Check for external command
 * @mycmd: The command to check for
 * Return: 0 on success
 */
int check_cmd(char *mycmd)
{
    if (chk_cmd_before_fork(mycmd) == 1 && s_strcmp(mycmd, "exit") != 0 &&
        s_strcmp(mycmd, "cd") != 0 && s_strcmp(mycmd, "setenv") != 0 &&
        s_strcmp(mycmd, "unsetenv") != 0 && s_strcmp(mycmd, "alias") != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

