#include "main.h"

/**
 * buffers - update buffers with new values
 * @all_str: pointer to all_strings to be set (char **)
 * @c_command: pointer to current_command to be set (char **)
 * @state: state of buffers (int)
 * Return: void
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void buffers(char **all_str, char **c_command, int state)
{
	static char **str;
	static char **command;

	if (all_str)
		str = all_str;
	if (c_command)
		command = c_command;
	if (state == 0)
	{
		_Free(*str);
		_Free(*command);
	}
}
/**
 * _enviornment - update environment with new values (char ***)
 * @envp: pointer to environment to be set (char **)
 * @state: state of enviornment (int)
 * Return: pointer to modified environment (char ***)
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
char ***_enviornment(char **envp, int state)
{
	static char **enviornment;

	if (state && envp)
	{
		enviornment = envp;
	}
	if (!state)
	{
		free_args(enviornment);
	}
	return (&enviornment);
}
/**
 * _state - update state with new values (int)
 * @c_state: state to be set (int)
 * Return: updated state (int)
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int _state(int c_state)
{
	static int state;

	if (c_state == Get_state)
	{
		return (state);
	}
	else
	{
		state = c_state;
		return (state);
	}
}
/**
 * _alias - establish alias with new values (char **)
 * @alias_arg: alias to be set (char *)
 * @state: state of alias (int)
 * Return: pointer to defined alias (char **)
* Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
char **_alias(char *alias_arg, int state)
{
	static char **alias_list;

	if (state && alias_arg && _strchr(alias_arg, '='))
	{
		char *temp = NULL;
		char *value = NULL;
		int i = 0;

		while (alias_arg[i] && alias_arg[i] != '=')
			i++;
		temp = _malloc(i + 1);
		_memcpy(temp, alias_arg, i);
		temp[i] = '\0';
		value = gt_alias_value(temp);
		if (value)
		{
			i = gt_alias_ind(temp);
			_Free(alias_list[i]);
			alias_list[i] = _strdup(alias_arg);
			_Free(value);
		}
		else
		{
			add_args(&alias_list, alias_arg);
		}
		_Free(temp);
		return (alias_list);
	}
	else if (state)
	{
		return (alias_list);
	}
	free_args(alias_list);
	return (NULL);
}
