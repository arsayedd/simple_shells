#include "new_shell.h"

/**
 * Prints a string to stderr.
 *
 * @param str The string to be printed.
 */
void new_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		new_eputchar(str[i]);
		i++;
	}
}

/**
 * Writes the character c to stderr.
 *
 * @param c The character to print.
 *
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int new_eputchar(char c)
{
	static int i;
	static char buf[NEW_WRITE_BUF_SIZE];

	if (c == NEW_BUF_FLUSH || i >= NEW_WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != NEW_BUF_FLUSH)
		buf[i++] = c;
	return 1;
}

/**
 * Writes the character c to the given file descriptor.
 *
 * @param c  The character to print.
 * @param fd The file descriptor to write to.
 *
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int new_putfd(char c, int fd)
{
	static int i;
	static char buf[NEW_WRITE_BUF_SIZE];

	if (c == NEW_BUF_FLUSH || i >= NEW_WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != NEW_BUF_FLUSH)
		buf[i++] = c;
	return 1;
}

/**
 * Prints an input string to the specified file descriptor.
 *
 * @param str The string to be printed.
 * @param fd  The file descriptor to write to.
 *
 * @return The number of characters put.
 */
int new_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return 0;
	while (*str)
	{
		i += new_putfd(*str++, fd);
	}
	return i;
}
