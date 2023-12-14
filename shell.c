#include "main.h"

/**
* main - entry point
* @argc: number of arguments
* @argv: array of arguments
* @envp: array of environment variables
* Return: 0 if successful, otherwise 1
* by Ahmed Raafat
*/
int main(int argc, char *argv[], char *envp[])
{
int act_mode = isatty(STDIN_FILENO);
char *symbol = "-> ";
int fd = STDIN_FILENO;
_state(0);
if (argc == 2)
check_files_type(argv[1], &fd, &act_mode);
__envit(dupl_2D(envp), 1);
shell_coress(symbol, fd, act_mode);
__envit(NULL, 0);
_alias(NULL, 0);
return (STATE);
}
/**
* check_files_type - check if file mode is active
* @filename: pointer to filename
* @fd: pointer to file descriptor
* @act_mode: pointer to active mode
* Return: void
* by Ahmed Raafat
*/
void check_files_type(char *filename, int *fd, int *act_mode)
{
if (access(filename, R_OK) != -1)
{
*act_mode = 0;
*fd = open(filename, O_RDONLY);
if (!files_size(filename))
exit(0);
}
else
{
print(STDERR_FILENO, "./hsh: 0: Can't open ", filename, "\n", NULL);
exit(127);
}
}

/**
* files_size - get the size of file
* @fname: pointer to filename
* Return: size of file
* by Ahmed Raafat
*/
int files_size(char *fname)
{
struct stat st;
stat(fname, &st);
return (st.st_size);
}
/**
* shell_cores - core of shell
* @symbol: pointer to symbol
* @fd: file descriptor
* @act_mode: active mode
* Return: void
* by Ahmed Raafat
*/
void shell_cores(char *symbol, int fd, int act_mode)
{
do {
char *input_buffer = _malloc(BUFFER_SIZE);
char *current_command = _malloc(BUFFER_SIZE);
int read_size = 0;
int buffer_size = BUFFER_SIZE;
int command_size = BUFFER_SIZE;
if (act_mode == 1)
print(STDOUT_FILENO, symbol, NULL);
gets_input(&input_buffer, &read_size, &buffer_size, fd);
buffers(&input_buffer, &current_command, 1);
gets_command(input_buffer, &current_command, &command_size);
while (*current_command)
{
hand_comm(current_command);
gets_command(input_buffer, &current_command, &command_size);
}
if (read_size == 0)
{
_free(input_buffer);
_free(current_command);
break;
}

_free(input_buffer);
_free(current_command);
} while (act_mode);
}
