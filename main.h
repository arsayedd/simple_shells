#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>

#define BUFFER_SIZE 255
#define GET_STATE -1024

#define ENVIRONMENT_PTR _environment(NULL, 1)
#define ENVIRONMENT (*_environment(NULL, 1))
#define ALIAS_LIST _alias(NULL, 1)
#define STATE _state(GET_STATE)
#define FREE(a) (_free((void *)&(a)))

extern char **environ;

int *_strchr(const char *str, int c);
char *_strtok(char *str, const char *delimiters);
char *_strtok2(char *str, const char *delimiters);
int _strlen(char *p_string);
char *_strdup(char *p_string);
char *_strcpy(char *copy_to, char *copy_from);
int _strcmp(char *string1, char *string2);
int _atoi(char *string);
char *_strcat(char *s1, char *s2);
void *_memcopy(char *copy_to, const char *copy_from, size_t n);
void get_input(char **buff, int *size, int *buffer_size, int source);
void get_command(char *str, char **c_command, int *cmd_size);
char *get_path(char *envp[]);
char check_many_commands(char *str);
void add_args(char ***arguments_array, char *argument);
void handle_command(char *command);
int execute_command(char *path, char **args);
char *find_path(char *path, char *input);
int handle_exec(char *c_path, char **argument);
void free_arguments(char **arguments);
int handle_error(char *first_segment, char *path);
void handle_current_command(char *first_segment, char **arguments);
int handle_exit(char **arguments);
int handle_builtin(char *first_segment, char **arguments);
int check_builtin(char *first_segment);
int check_exit_argument(char *str);
int handle_env(char *envp[]);
int h_env(void);
char **duplicate_2D(char *list[]);
int handle_setenv(char *argv[]);
void free_buffer(char *str);
int handle_unsetenv(char *argv[]);
char *_strstr(char *the_big_str, char *the_little_str);
void handle_str_spaces(char *str, int str_size);
int check_spaces(char *str, int i);
void initialize_NULL(char *str, int size);
int handle_cd(char **arguments);
char *get_env_value(char *key);
char **create_2D(int size, ...);
void edit_command(char **str_ptr, int *str_size);
void nts_recursive_helper(int num, char result[], int *index);
void nts(int num, char result[]);
void handle_scape(char *str);
void *_realloc(void *ptr, int new_size);
void buffers(char **all_str, char **c_command, int state);
int empty_text(char *str);
int remove_read_spaces(char *str);
void _free(void **ptr);
char ***_environment(char **envp, int state);
int _state(int c_state);
char *replace_text_index(char **str1, char *str2, int start_index, int end_index);
int file_size(char *fname);
int last_space(char *str);
char **_alias(char *alias_arg, int state);
int handle_alias(char **arguments);
int print_all_alias(void);
int print_one_alias(char *key);
void alias_replace(char **str_ptr, int *str_size);
char *get_alias_value(char *key);
int get_alias_index(char *key);
void print(int fd, ...);
void *_malloc(unsigned int size);
int _read(int fd, char *str, int str_size);
void remove_read_spaces_helper(char *str, int str_size);
void get_command_helper(char *str, char **c_command, int *cmd_size, int *i, int *j);
void edit_command_helper(char **str_ptr, char **str, char *temp, int *index);
int handle_command_helper(char *first_segment, char **arguments, char c);
void check_file_mode(char *filename, int *fd, int *active_mode);
void shell_core(char *symbol, int fd, int active_mode);
int handle_cd_helper(char **arguments, char **pwd, char **oldpwd, char *cd, char *cwd);

#endif
