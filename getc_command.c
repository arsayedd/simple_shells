#include "main.h"

/**
 * gets_command - Extracts a command from user input (char *)
 * @str: User input (char *)
 * @c_command: Pointer to the command to be returned (char **)
 * @cmd_size: Pointer to the size of the command to be returned (int *)
 * Return: void
 * by Ahmed Raafat & Ahmed Abdelnasser
 */

void gets_command(char *str, char **c_command, int *cmd_size)
{
	int i = 0, j = 0;

	while (str[i] == 2 || str[i] == ' ')
	{
		i++;
	}
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (str[i + 1] != '\n')
			{
				str[i] = 2;
				break;
			}
			else
			{
				str[i] = 2;
				i++;
			}
		}
		else if (str[i] == ' ' && !lst_space(str + i))
			break;

		else if (str[i] == ' ' && str[i + 1] == ' ')
		{
			i++;
			continue;
		}
		else
			gets_comm_help(str, c_command, cmd_size, &i, &j);
	}
	(*c_command)[j] = '\0';
	alias_change(c_command, cmd_size);
	edit_comm(c_command, cmd_size);
}

/**
 * lst_space - Checks if the last char in the string is a space
 * @str: String to check (char *)
 * Return: (1) if the last char in the string is space, (0) otherwise (int)
 * by Ahmed Raafat & Ahmed Abdelnasser
 */

int lst_space(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i++] != ' ')
			return (1);
	}
	return (0);
}

/**
 * gets_comm_help - Helper function for gets_command
 * @str: User input (char *)
 * @c_command: Pointer to the command to be returned (char **)
 * @cmd_size: Pointer to the size of the command to be returned (int *)
 * @i: Pointer to the index of user input (int *)
 * @j: Pointer to the index of the command to be returned (int *)
 * Return: void
 * by Ahmed Raafat & Ahmed Abdelnasser
 */

void gets_comm_help(char *str, char **c_command,
						 int *cmd_size, int *i, int *j)
{
	if (*j < *cmd_size - 2)
	{
		(*c_command)[*j] = str[*i];
		str[*i] = 2;
		*i += 1;
		*j += 1;
	}
	else
	{
		*c_command = _realloc(*c_command, *cmd_size * 2);
		*cmd_size *= 2;
		buffers(NULL, c_command, 1);
	}
}

/**
 * edit_comm - Edits the command to replace $$, $?, and $<env>
 * @str_ptr: Pointer to the command to be edited (char **)
 * @str_size: Pointer to the size of the command to be edited (int *)
 * Return: void
 * by Ahmed Raafat & Ahmed Abdelnasser
 */

void edit_comm(char **str_ptr, int *str_size)
{
	int i = 0;
	int temp_size = *str_size;
	char *temp = malloc(temp_size);
	char *str = *str_ptr;

	for (i = 0; str[i]; i++)
	{
		if (_strcmp(str + i, "$$") == 0)
		{
			char pid[255];

			nts(getpid(), pid);

			str = replaceTxtInd(str_ptr, pid, i, i + 1);
			i += _strllen(pid) - 1;
		}
		else if (_strcmp(str + i, "$?") == 0)
		{
			char last_exit_code[255];

			nts(State, last_exit_code);

			str = replaceTxtInd(str_ptr, last_exit_code, i, i + 1);
			i += _strllen(last_exit_code) - 1;
		}
		else if (str[i] == '$' && str[i + 1] != '$' &&
				 str[i + 1] != ' ' && str[i + 1])
		{
			edit_comm_helper(str_ptr, &str, temp, &i);
		}
		else if (str[i] == '#')
		{
			if ((i && str[i - 1] == ' ') || !i)
				str[i] = '\0';
			break;
		}
	}
	_Free(temp);
}

/**
 * edit_comm_helper - Helper function for edit_comm to replace $<env>
 * @str_ptr: Pointer to the command to be edited (char **) (copy of str)
 * @str: Pointer to the command to be edited (char *) (copy of str_ptr)
 * @temp: Pointer to the temp string (char *) to be used in editing
 * @index: Pointer to the index of the command to be edited (int *) (copy of i)
 * Return: void (edited command is returned through str_ptr)
 * by Ahmed Raafat & Ahmed Abdelnasser
 */

void edit_comm_helper(char **str_ptr,
						 char **str, char *temp, int *index)
{
	char *value;
	int j = 0, i = *index;

	while ((*str)[i + j] && (*str)[i + j] != ' ')
		j++;
	_memecopy(temp, (*str) + i + 1, j - 1);
	temp[j - 1] = '\0';
	value = get_env_value(temp);
	if (value)
	{
		*str = replaceTxtInd(str_ptr, value, i, i + j - 1);
		*index += _strllen(value) - 1;
		_Free(value);
	}
	else
	{
		*str = replaceTxtInd(str_ptr, " ", i, i + j - 1);
	}
}
