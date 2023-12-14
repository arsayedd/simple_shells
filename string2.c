#include "shell.h"

/**
 * s_strchr - Returns a pointer to the first occurrence of a character.
 * @string: The string to search.
 * @chr: The character searching for.
 * Return: Pointer to the search character or NULL if not found.
 */
char *s_strchr(const char *string, int chr)
{
	while (*string != '\0')
	{
		if (*string == (char)chr)
			return (char *)string;

		string++;
	}
	return NULL;
}

/**
 * s_strtok - Tokenizes a string.
 * @str: The string to tokenize.
 * @delim: The delimiter to use.
 * Return: The tokenized string or NULL if no more tokens are found.
 */
char *s_strtok(char *str, const char *delim)
{
	static char *token;
	char *start;
	char *end;

	if (str != NULL)
	{
		token = str;
	}
	else if (token == NULL)
	{
		return NULL;
	}

	while (is_delimiter(*token, delim))
	{
		token++;
	}

	if (*token == '\0')
	{
		return NULL;
	}

	start = token;
	end = start;

	while (*end != '\0')
	{
		if (is_delimiter(*end, delim))
		{
			*end = '\0';
			token = end + 1;
			return start;
		}
		end++;
	}

	token = end;
	return start;
}

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @c: The character.
 * @delim: The delimiter.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
		{
			return 1;
		}
		delim++;
	}
	return 0;
}

/**
 * s_strncmp - Compares two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 * Return: Less than 0 if s1 is shorter than s2, 0 if they match,
 *         and greater than 0 if s1 is longer than s2.
 */
int s_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return s1[i] - s2[i];
		else if (s1[i] < s2[i])
			return s1[i] - s2[i];
	}

	if (i == n)
		return 0;
	else
		return -15;
}
