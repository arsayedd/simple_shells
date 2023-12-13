#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

/**
 * enum _boolean - enumeration to use true and false
 * @false: 0
 * @true: 1
 */
typedef enum _boolean
{
    false = 0,
    true = 1
} Boolean;

typedef enum custom_errors
{
    READLINE = 0
} CustomErrors;

/**
 * struct custom_list - struct defining a linked list
 * @dir: a directory path
 * @next: a pointer to another struct custom_list
 */
typedef struct custom_list
{
    char *dir;
    struct custom_list *next;
} CustomList;

/**
 * struct custom_builtin - defines builtin commands
 * @name: the builtin command's name
 * @f: function pointer to the builtin command
 */
typedef struct custom_builtin
{
    char *name;
    int (*f)(char **argv, char **front);
} CustomBuiltin;

/**
 * struct custom_alias - defines aliases
 * @name: alias' name
 * @value: alias' value
 * @next: a pointer to the next alias
 */
typedef struct custom_alias
{
    char *name;
    char *value;
    struct custom_alias *next;
} CustomAlias;

#endif /* CUSTOM_TYPES_H */
