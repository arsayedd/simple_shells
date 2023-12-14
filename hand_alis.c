#include "main.h"

/**
 * hand_alias - process alias command (char **)
 * @arguments: arguments for alias command (char **)
 * Return: 0 on success, 1 on failure
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int hand_alias(char **arguments)
{
	int state = 0;
	int i = 0;

	if (arguments[1] && arguments[1][0])
	{
		while (arguments[++i])
			if (_strchr(arguments[i], '='))
			{
				_alias(arguments[i], 1);
			}
			else
			{
				state = pt_one_alias(arguments[i]);
			}
	}
	else
	{
		state = pt_all_alias();
	}
	free_args(arguments);
	return (state);
}
/**
 * pt_one_alias - print a single alias
 * @key: key to print (char *)
 * Return: 0 on success, 1 on failure
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int pt_one_alias(char *key)
{

	int i = 0;
	char **alias_lisr = Alias_list;

	if (alias_lisr && key)
		while (alias_lisr[i])
		{
			if (_strstr(alias_lisr[i], key) == alias_lisr[i] &&
				alias_lisr[i][_strlen(key)] == '=')
			{
				char *str = _strdup(alias_lisr[i]);
				char *ptr = _strstr(str, "=");
				*ptr = '\0';
				print(STDOUT_FILENO, str, "='", ptr + 1, "'\n", NULL);
				_Free(str);
				return (0);
			}
			i++;
		}
	return (0);
}
/**
 * gt_alias_value - obtain value of alias
 * @key: key to get value of (char *)
 * Return: value of alias (char *)
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
char *gt_alias_value(char *key)
{
	char *path = NULL;
	char *cur_env = NULL;
	char *value = NULL;
	int i = 0;
	char **alias_list = Alias_list;

	if (key && *key && alias_list)
	{
		path = _strdup(key);
		path = _realloc(path, _strlen(path) + 2);
		_strcat(path, "=");

		while (alias_list[i])
		{
			cur_env = alias_list[i];
			if (_strstr(cur_env, path) == cur_env)
			{
				value = _strdup(cur_env + _strlen(path));
				_Free(path);
				return (value);
			}
			i++;
		}
	}
	_Free(path);
	return (value);
}
/**
 * gt_alias_ind - determine index of alias
 * @key: key to find the index of (char *)
 * Return: index of the alias (int)
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int gt_alias_ind(char *key)
{
	char *path = NULL;
	char *cur_env = NULL;
	int i = 0;
	char **alias_list = Alias_list;

	if (key && *key && alias_list)
	{
		path = _strdup(key);
		path = _realloc(path, _strlen(path) + 2);
		_strcat(path, "=");

		while (alias_list[i])
		{
			cur_env = alias_list[i];
			if (_strstr(cur_env, path) == cur_env)
			{
				_Free(path);
				return (i);
			}
			i++;
		}
	}
	_Free(path);
	return (-1);
}
/**
 * alias_change - change alias in command
 * @str_ptr: pointer to command (char **)
 * @str_size: pointer to size of command (int *)
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void alias_change(char **str_ptr, int *str_size)
{
	int i = 0;
	char *temp = _malloc(*str_size);
	char *str = *str_ptr;
	char *value = NULL;

	while (1)
	{
		i = 0;
		while (str[i] && str[i] != ' ')
			i++;
		_memcpy(temp, str, i);
		temp[i] = '\0';
		value = gt_alias_value(temp);
		if (value)
		{
			str = replaceTxtInd(str_ptr, value, 0, i - 1);
			_Free(value);
		}
		else
		{
			break;
		}
	}
	_Free(temp);
}
