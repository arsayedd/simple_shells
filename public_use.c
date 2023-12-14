#include "main.h"

/**
* adjust Buffers - fine-tune buffer values
* @strArray: pointer to strArray to be fine-tuned (char **)
* @currentCmd: pointer to currentCmd for adjustments (char **)
* @buffer Status: status of buffers (int)
* Authors: Ahmed Raafat & Ahmed Abdelanasser
* Brief: This function refines the buffer values.
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
* _envit - set enviornment to new values (char ***)
* @envp: pointer to envp to be set (char **)
* @state: state of enviornment (int)
* Return: pointer to enviornment (char ***)
* by ashraf & ramzy
*/
char ***_envit(char **envp, int state)
{
static char **enviornment;

if (state && envp)
{
enviornment = envp;
}
if (!state)
{
free_arguments(enviornment);
}
return (&enviornment);
}
/**
* _states - set state to new values (int)
* @c_state: state to be set (int)
* Return: state (int)
* by ashraf & ramzy
*/
int _states(int c_state)
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
* _alias - set alias to new values (char **)
* @alias_arg: alias to be set (char *)
* @state: state of alias (int)
* Return: pointer to alias (char **)
* by ashraf & ramzy
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
_memecopy(temp, alias_arg, i);
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
free_arguments(alias_list);
return (NULL);
}
