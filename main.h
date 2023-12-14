#ifndef main_h
#define main_h
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
#define ENV_PTR _envit(NULL, 1)
#define ENV (*_envit(NULL, 1))
#define ALIAS_LIST _alias(NULL, 1)
#define STATE _state(GET_STATE)
#define FREE(a) (_free((void *)&(a)))
extern char **envi;
int *_stchr(const char *str, int c);
char *_strttok(char *str, const char *delimiters);
char *_strttok2(char *str, const char *delimiters);
int _strllen(char *p_string);
char *_strddup(char *p_string);
char *_strccpy(char *copy_to, char *copy_from);
int _strccmp(char *string1, char *string2);
int _atoi(char *string);
char *_strccat(char *s1, char *s2);
void *_memecopy(char *copy_to, const char *copy_from, size_t n);
void gets_input(char **buff, int *size, int *buffer_size, int source);
void gets_command(char *str, char **c_command, int *cmd_size);
char *gets_path(char *envp[]);
char check_many_comm(char *str);
void add_args(char ***arguments_array, char *argument);
void hand_comm(char *command);
int execute_comm(char *path, char **args);
char *find_paths(char *path, char *input);
int handle_execu(char *c_path, char **argument);
void free_args(char **arguments);
int hand_errors(char *first_segment, char *path);
void hand_curr_comm(char *first_segment, char **arguments);
int hand_exits(char **arguments);
int hand_builtin(char *first_segment, char **arguments);
int check_builtin(char *first_segment);
int check_exit_arg(char *str);
int hand_env(char *envp[]);
int hd_env(void);
char **dupl_2D(char *list[]);
int hand_setenvs(char *argv[]);
void free_buff(char *str);
int hand_unstenv(char *argv[]);
char *_strstr(char *the_big_str, char *the_little_str);
void hand_str_spaces(char *str, int str_size);
int see_spaces(char *str, int i);
void initialize_NULL(char *str, int size);
int hand_cd(char **arguments);
char *get_envs_val(char *key);
char **build_2D(int size, ...);
void edit_comm(char **str_ptr, int *str_size);
void nts_recursive_hlp(int num, char result[], int *index);
void nts(int num, char result[]);
void hand_scape(char *str);
void *_realloc(void *ptr, int new_size);
void buffers(char **all_str, char **c_command, int state);
int zero_text(char *str);
int delete_read_spaces(char *str);
void _free(void **ptr);
char ***_envit(char **envp, int state);
int _states(int c_state);
char *replaceTxtInd(char **str1, char *str2,
int start_ind, int end_ind);
int files_size(char *fname);
int lst_space(char *str);
char **_alias(char *alias_arg, int state);
int hand_alias(char **arguments);
int pt_all_alias(void);
int pt_one_alias(char *key);
void alias_change(char **str_ptr, int *str_size);
char *gt_alias_value(char *key);
int gt_alias_ind(char *key);
void print(int fd, ...);
void *_malloc(unsigned int size);
int _read(int fd, char *str, int str_size);
void remove_read_spaces_hlp(char *str, int str_size);
void gets_comm_help(char *str, char **c_command,
int *cmd_size, int *i, int *j);
void edit_comm_hlp(char **str_ptr, char **str, char *temp, int *index);
int hand_comm_hlp(char *first_segment, char **arguments, char c);
void check_files_type(char *filename, int *fd, int *act_mode);
void shell_cores(char *symbol, int fd, int act_mode);
int hand_cd_helper(char **arguments, char **pwd,
char **oldpwd, char *cd, char *cwd);
#endif
