#include "shell.h"

/**
 * removeComment - Removes comments from the user command.
 * @command: The user command.
 * Return: Void.
 */
void removeComment(char *command)
{
	int number = 0;
	int inQuotes = 0;

	while (command[number] != '\0')
	{
		if (command[number] == '"')
		{
			inQuotes = !inQuotes;
		}
		else if (!inQuotes && command[number] == '#' && isWordStart(command, number))
		{
			command[number] = '\0';
			break;
		}
		number++;
	}
}

/**
 * intToString - Converts an integer to a string.
 * @value: The integer.
 * @str: The string where the result is stored.
 * @size: The length of the string.
 * Return: Void.
 */
void intToString(int value, char *str, int size)
{
	int index = size - 1;

	str[index] = '\0';
	do
	{
		index--;
		str[index] = '0' + (value % 10);
		value /= 10;
	} while (value != 0 && index > 0);
}

/**
 * stringCopyLimited - Copies a string up to a specified number of characters.
 * @source: The string to copy from.
 * @n: The number of characters to copy.
 * Return: The copied string.
 */
char *stringCopyLimited(char *source, size_t n)
{
	char *destination = NULL;
	size_t length = 0;
	size_t i;

	while (source[length] != '\0' && length < n)
	{
		length++;
	}

	destination = (char *)malloc(length + 1);

	if (destination)
	{
		for (i = 0; i < length; i++)
		{
			destination[i] = source[i];
		}

		destination[length] = '\0';
	}

	return destination;
}

/**
 * isAlphanumeric - Checks if a character is alphanumeric.
 * @c: The character.
 * Return: The absolute int.
 */
int isAlphanumeric(unsigned char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || (c == '_'));
}

