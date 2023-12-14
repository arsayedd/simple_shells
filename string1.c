#include "shell.h"

/**
 * s_strdup - Duplicates a string.
 * @string: The string to copy.
 * Return: A duplicated string or NULL if allocation fails.
 */
char *s_strdup(const char *string)
{
	if (string == NULL)
		return NULL;

	int len = s_strlen(string);
	char *copy = malloc(len + 1);

	if (copy == NULL)
		return NULL;

	s_strcpy(copy, string);
	return copy;
}

/**
 * s_strlen - Returns the length of a string.
 * @string: The string.
 * Return: The length of the string.
 */
int s_strlen(const char *string)
{
	int index = 0;

	while (string[index] != '\0')
		index++;

	return index;
}

/**
 * s_strcspn - Returns the index of the first occurrence of a character.
 * @string: The string to search.
 * @chr: The character to search for.
 * Return: The index of the search or the length of the string if not found.
 */
int s_strcspn(const char *string, const char *chr)
{
	int index = 0;

	while (string[index] != '\0')
	{
		int charindex = 0;

		while (chr[charindex] != '\0')
		{
			if (string[index] == chr[charindex])
				return index;

			charindex++;
		}

		index++;
	}

	return index;
}

/**
 * s_strcpy - Copies the content of one string to another.
 * @dest_string: The destination string.
 * @src_string: The source string.
 * Return: Pointer to the destination string.
 */
char *s_strcpy(char *dest_string, const char *src_string)
{
	while (*src_string != '\0')
	{
		*dest_string = *src_string;
		dest_string++;
		src_string++;
	}

	*dest_string = '\0';
	return dest_string;
}
