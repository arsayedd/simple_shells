#include "main.h"

/**
 * getc_command - extract command from user input
 * @str: user input (char *)
 * @c_command: pointer to extracted command (char **)
 * @cmd_size: pointer to size of extracted command (int *)
 * Return: void
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void getc_command(char *str, char **c_command, int *cmd_size)
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
 * lst_space - verify if the last character in a string is a space
 * @str: string to examine (char *)
 * Return: (1) if the last character is a space, (0) otherwise (int)
* Authors: Ahmed Raafat & Ahmed Abdelanasser
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
 * gets_comm_help - auxiliary function for extracting command
 * @str: user input (char *)
 * @c_command: pointer to extracted command (char **)
 * @cmd_size: pointer to size of extracted command (int *)
 * @i: pointer to index of user input (int *)
 * @j: pointer to index of extracted command (int *)
 * Return: void
* Authors: Ahmed Raafat & Ahmed Abdelanasser
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
 * edit_comm - adjust command to replace $$, $?, and $<env>
 * @str_ptr: pointer to command to be adjusted (char **)
 * @str_size: pointer to size of command to be adjusted (int *)
 * Return: void
* Authors: Ahmed Raafat & Ahmed Abdelanasser
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
			i += _strlen(pid) - 1;
		}
		else if (_strcmp(str + i, "$?") == 0)
		{
			char last_exit_code[255];

			nts(State, last_exit_code);

			str = replaceTxtInd(str_ptr, last_exit_code, i, i + 1);
			i += _strlen(last_exit_code) - 1;
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
 * edit_comm_helper - auxiliary function for adjusting command with $<env>
 * @str_ptr: pointer to command to be adjusted (char **) (copy of str)
 * @str: pointer to command to be adjusted (char *) (copy of str_ptr)
 * @temp: pointer to temporary string (char *) for editing
 * @index: pointer to index of command to be adjusted (int *) (copy of index)
 * Return: void (adjusted command is returned through command_ptr)
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void edit_comm_helper(char **str_ptr,
						 char **str, char *temp, int *index)
{
	char *value;
	int j = 0, i = *index;

	while ((*str)[i + j] && (*str)[i + j] != ' ')
		j++;
	_memcpy(temp, (*str) + i + 1, j - 1);
	temp[j - 1] = '\0';
	value = get_envs_val(temp);
	if (value)
	{
		*str = replaceTxtInd(str_ptr, value, i, i + j - 1);
		*index += _strlen(value) - 1;
		_Free(value);
	}
	else
	{
		*str = replaceTxtInd(str_ptr, " ", i, i + j - 1);
	}
}
