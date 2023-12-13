#ifndef NEW_SHELL_H
#define NEW_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define NEW_READ_BUF_SIZE 1024
#define NEW_WRITE_BUF_SIZE 1024
#define NEW_BUF_FLUSH -1

/* for command chaining */
#define NEW_CMD_NORM 0
#define NEW_CMD_OR 1
#define NEW_CMD_AND 2
#define NEW_CMD_CHAIN 3

/* for convert_number() */
#define NEW_CONVERT_LOWERCASE 1
#define NEW_CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define NEW_USE_GETLINE 0
#define NEW_USE_STRTOK 0

#define NEW_HIST_FILE ".simple_shell_history"
#define NEW_HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} new_list_t;

/**
 *struct passinfo - contains pseudo-arguments to pass into a function,
 *                  allowing a uniform prototype for the function pointer struct
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: NEW_CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    new_list_t *env;
    new_list_t *history;
    new_list_t *alias;
    char **environ;
    int env_changed;
    int status;

    char **new_cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
    int new_cmd_buf_type; /* NEW_CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} new_info_t;

#define NEW_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
    char *type;
    int (*func)(new_info_t *);
} new_builtin_table;

/* new_hsh.c */
int new_hsh(new_info_t *, char **);
int find_new_builtin(new_info_t *);
void find_new_cmd(new_info_t *);
void new_fork_cmd(new_info_t *);

/* new_path.c */
int is_new_cmd(new_info_t *, char *);
char *new_dup_chars(char *, int, int);
char *find_new_path(new_info_t *, char *, char *);

/* new_loophsh.c */
int new_loophsh(char **);

/* new_err_string_functions.c */
void new_eputs(char *);
int new_eputchar(char);
int new_putfd(char c, int fd);
int new_putsfd(char *str, int fd);

/* new_string_functions.c */
int new_strlen(char *);
int new_strcmp(char *, char *);
char *new_starts_with(const char *, const char *);
char *new_strcat(char *, char *);

/* new_string_functions2.c */
char *new_strcpy(char *, char *);
char *new_strdup(const char *);
void new_puts(char *);
int new_putchar(char);

/* new_string_functions3.c */
char *new_strncpy(char *, char *, int);
char *new_strncat(char *, char *, int);
char *new_strchr(char *, char);

/* new_string_functions4.c */
char **new_strtow(char *, char *);
char **new_strtow2(char *, char);

/* new_memory_functions */
char *new_memset(char *, char, unsigned int);
void new_ffree(char **);
void *new_realloc(void *, unsigned int, unsigned int);

/* new_memory_functions2.c */
int new_bfree(void **);

/* new_more_functions.c */
int new_interactive(new_info_t *);
int is_new_delim(char, char *);
int new_isalpha(int);
int new_atoi(char *);

/* new_more_functions2.c */
int new_erratoi(char *);
void print_new_error(new_info_t *, char *);
int new_print_d(int, int);
char *convert_new_number(long int, int, int);
void remove_new_comments(char *);

/* new_builtin_emulators.c */
int new_myexit(new_info_t *);
int new_mycd(new_info_t *);
int new_myhelp(new_info_t *);

/* new_builtin_emulators2.c */
int new_myhistory(new_info_t *);
int new_myalias(new_info_t *);

/* new_getline.c module */
ssize_t get_new_input(new_info_t *);
int new_getline(new_info_t *, char **, size_t *);
void new_sigintHandler(int);

/* new_info.c module */
void clear_new_info(new_info_t *);
void set_new_info(new_info_t *, char **);
void free_new_info(new_info_t *, int);

/* new_env.c module */
char *new_getenv(new_info_t *, const char *);
int new_myenv(new_info_t *);
int new_mysetenv(new_info_t *);
int new_myunsetenv(new_info_t *);
int populate_new_env_list(new_info_t *);

/* new_env2.c module */
char **get_new_environ(new_info_t *);
int new_unsetenv(new_info_t *, char *);
int new_setenv(new_info_t *, char *, char *);

/* new_file_io_functions.c */
char *get_new_history_file(new_info_t *info);
int write_new_history(new_info_t *info);
int read_new_history(new_info_t *info);
int build_new_history_list(new_info_t *info, char *buf, int linecount);
int renumber_new_history(new_info_t *info);

/* new_liststr.c module */
new_list_t *add_new_node(new_list_t **, const char *, int);
new_list_t *add_new_node_end(new_list_t **, const char *, int);
size_t print_new_list_str(const new_list_t *);
int delete_new_node_at_index(new_list_t **, unsigned int);
void new_free_list(new_list_t **);

/* new_liststr2.c module */
size_t new_list_len(const new_list_t *);
char **new_list_to_strings(new_list_t *);
size_t print_new_list(const new_list_t *);
new_list_t *node_starts_with(new_list_t *, char *, char);
ssize_t get_new_node_index(new_list_t *, new_list_t *);

/* new_chain.c */
int is_new_chain(new_info_t *, char *, size_t *);
void check_new_chain(new_info_t *, char *, size_t *, size_t, size_t);
int replace_new_alias(new_info_t *);
int replace_new_vars(new_info_t *);
int replace_new_string(char **, char *);

#endif
