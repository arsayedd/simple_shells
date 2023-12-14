#include "main.h"

/**
* get_input - Retrieves input from the user
* @buff: Pointer to the buffer to store input (char **)
* @size: Pointer to the size of input to be returned (int *)
* @buffer_size: Pointer to the size of the buffer to be returned (int *)
* @source: Source of input (int)
* Return: void
* by Ahmed Raafat & Ahmed Abdelnasser
*/
void get_input(char **buff, int *size, int *buffer_size, int source)
{
int max_read = *buffer_size - 1;
int read = max_read;
char *temp = _malloc(max_read + 1);

intail_NULL(temp, max_read + 1);
while (read == max_read)
{
read = _read(source, temp, max_read);
*size += remove_read_spaces(temp);

if (*size > *buffer_size - 1)
{
*buff = _realloc(*buff, *size + 1);
*buffer_size = *size;
}
_strcat(*buff, temp);
buffers(buff, NULL, 1);
}
_Free(temp);
handle_str_spaces(*buff, *buffer_size);
}

/**
* handle_str_spaces - Handles spaces in a string
* @str: String to handle spaces in (char *)
* @str_size: Size of the string to handle spaces in (int)
* Return: void
* by Ahmed Raafat & Ahmed Abdelnasser
*/
void handle_str_spaces(char *str, int str_size)
{
int i = 0;
char *temp = _malloc(str_size);

intail_NULL(temp, BUFFER_SIZE);
while (str && str[i])
{
if (check_spaces(str, i) == 1)
{
_strcpy(temp, str);
str[i] = ' ';
_strcpy(str + i + 1, temp + i);
}
else if (check_spaces(str, i) == 2)
{
_strcpy(temp, str);
str[++i] = ' ';
_strcpy(str + i + 1, temp + i);
}
else if (check_spaces(str, i) == 3)
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
* remove_read_spaces - Removes spaces from a string
* @str: String to remove spaces from (char *)
* Return: Size of the string after removing spaces (int)
* by Ahmed Raafat & Ahmed Abdelnasser
*/
int remove_read_spaces(char *str)
{
int strSize = _strlen(str);
int i = 0;

while (str[i] == ' ')
i++;
if (i)
{
if (i == strSize - 2)
{
intail_NULL(str, strSize);
return (0);
}
else
{
char *ptr = str + i;

_strcpy(str, ptr);
}
}
remove_read_spaces_helper(str, strSize);
return (_strlen(str));
}

/**
* remove_read_spaces_helper - Helper function for remove_read_spaces
* @str: String to remove spaces from (char *)
* @strSize: Size of the string to remove spaces from (int)
* Return: void
* by Ahmed Raafat & Ahmed Abdelnasser
*/
void remove_read_spaces_helper(char *str, int strSize)
{
int i = 0;

while (str[i])
{
if (str[i] == ' ' && str[i + 1] == ' ')
{
int j = empty_text(str + i + 1);

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
intail_NULL(ptr, strSize);
}
}
i++;
}
}

/**
* check_spaces - Checks if there are spaces in a string
* @str: String to check (char *)
* @i: Index to check from (int)
* Return:
* (1) if there is a space before ;,
* (2) if there is a space after ;,
* (3) if there is a space before && or ||, (0) otherwise (int)
* by Ahmed Raafat & Ahmed Abdelnasser
*/
int check_spaces(char *str, int i)
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
