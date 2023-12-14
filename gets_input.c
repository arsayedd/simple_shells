#include "main.h"

/**
 * get_input - acquire input from user
 * @buff: pointer to buffer to store input (char **)
 * @size: pointer to size of input to be returned (int *)
 * @buffer_size: pointer to size of buffer to be returned (int *)
 * @source: source of input (int)
 * Return: void
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void get_input(char **buff, int *size, int *buffer_size, int source)
{
	int max_read = *buffer_size - 1;
	int read = max_read;
	char *temp = _malloc(max_read + 1);

	initialize_NULL(temp, max_read + 1);
	while (read == max_read)
	{
		read = _read(source, temp, max_read);
		*size += delete_read_spaces(temp);

		if (*size > *buffer_size - 1)
		{
			*buff = _realloc(*buff, *size + 1);
			*buffer_size = *size;
		}
		_strcat(*buff, temp);
		buffers(buff, NULL, 1);
	}
	_Free(temp);
	hand_str_spaces(*buff, *buffer_size);
}
/**
 * hand_str_spaces - manage spaces within a string
 * @str: string to manage spaces in (char *)
 * @str_size: size of the string to manage spaces in (int)
 * Return: void
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void hand_str_spaces(char *str, int str_size)
{
	int i = 0;
	char *temp = _malloc(str_size);

	initialize_NULL(temp, BUFFER_SIZE);
	while (str && str[i])
	{
		if (see_spaces(str, i) == 1)
		{
			_strcpy(temp, str);
			str[i] = ' ';
			_strcpy(str + i + 1, temp + i);
		}
		else if (see_spaces(str, i) == 2)
		{
			_strcpy(temp, str);
			str[++i] = ' ';
			_strcpy(str + i + 1, temp + i);
		}
		else if (see_spaces(str, i) == 3)
		{
			_strcpy(temp, str);
			i += 2;
			str[i] = ' ';
			_strcpy(str + i + 1, temp + i);
		}
		i++;
	}
	_Free(temp);
}
/**
 * delete_read_spaces - eliminate spaces from a string
 * @str: string to eliminate spaces from (char *)
 * Return: size of string after eliminating spaces (int)
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int delete_read_spaces(char *str)
{
	int strSize = _strlen(str);
	int i = 0;

	while (str[i] == ' ')
		i++;
	if (i)
	{
		if (i == strSize - 2)
		{
			initialize_NULL(str, strSize);
			return (0);
		}
		else
		{
			char *ptr = str + i;

			_strcpy(str, ptr);
		}
	}
	remove_read_spaces_hlp(str, strSize);
	return (_strlen(str));
}
/**
 * remove_read_spaces_hlp - auxiliary function for eliminating spaces
 * @str: string to eliminate spaces from (char *)
 * @strSize: size of string to eliminate spaces from (int)
 * Return: void
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void remove_read_spaces_hlp(char *str, int strSize)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			int j = zero_text(str + i + 1);

			if (j)
			{
				char *ptr = str + i + 1;
				char *ptr2 = str + i + j + 1;

				_strcpy(ptr, ptr2);
			}
			else
			{
				char *ptr = str + i;

				strSize = _strlen(str);
				initialize_NULL(ptr, strSize);
			}
		}
		i++;
	}
}
/**
 * see_spaces - examine spaces within a string
 * @str: string to inspect (char *)
 * @i: index to start inspection from (int)
 * Return:
 * (1) if there is a space before ;,
 * (2) if there is a space after ;,
 * (3) if there is a space before && or ||, (0) otherwise (int)
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int see_spaces(char *str, int i)
{
	if (i && str[i] == ';' && str[i - 1] != ' ')
	{
		return (1);
	}
	else if (str[i] == ';' && str[i + 1] != ' ')
	{
		return (2);
	}
	else if (_strstr(str + i, "&&") == str + i ||
			 _strstr(str + i, "||") == str + i)
	{
		if (i && str[i - 1] != ' ')
			return (1);
		else if (str[i + 2] != ' ')
			return (3);
		else
			return (0);
	}
	else
		return (0);
}
