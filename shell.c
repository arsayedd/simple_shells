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
int active_mode = isatty(STDIN_FILENO);
char *symbol = "-> ";
int fd = STDIN_FILENO;
_state(0);
if (argc == 2)
check_file_mode(argv[1], &fd, &active_mode);
_environment(duplicate_2D(envp), 1);
shell_core(symbol, fd, active_mode);
_environment(NULL, 0);
_alias(NULL, 0);
return (STATE);
}
/**
* check_file_mode - check if file mode is active
* @filename: pointer to filename
* @fd: pointer to file descriptor
* @active_mode: pointer to active mode
* Return: void
* by Ahmed Raafat
*/
void check_file_mode(char *filename, int *fd, int *active_mode)
{
if (access(filename, R_OK) != -1)
{
*active_mode = 0;
*fd = open(filename, O_RDONLY);
if (!file_size(filename))
exit(0);
}
else
{
print(STDERR_FILENO, "./hsh: 0: Can't open ", filename, "\n", NULL);
exit(127);
}
}

/**
* file_size - get the size of file
* @fname: pointer to filename
* Return: size of file
* by Ahmed Raafat
*/
int file_size(char *fname)
{
struct stat st;
stat(fname, &st);
return (st.st_size);
}
/**
* shell_core - core of shell
* @symbol: pointer to symbol
* @fd: file descriptor
* @active_mode: active mode
* Return: void
* by Ahmed Raafat
*/
void shell_core(char *symbol, int fd, int active_mode)
{
do {
char *input_buffer = _malloc(BUFFER_SIZE);
char *current_command = _malloc(BUFFER_SIZE);
int read_size = 0;
int buffer_size = BUFFER_SIZE;
int command_size = BUFFER_SIZE;
if (active_mode == 1)
print(STDOUT_FILENO, symbol, NULL);
get_input(&input_buffer, &read_size, &buffer_size, fd);
buffers(&input_buffer, &current_command, 1);
get_command(input_buffer, &current_command, &command_size);
while (*current_command)
{
handle_command(current_command);
get_command(input_buffer, &current_command, &command_size);
}
if (read_size == 0)
{
_free(input_buffer);
_free(current_command);
break;
}

_free(input_buffer);
_free(current_command);
} while (active_mode);
}
