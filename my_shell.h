#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void _eputs(char *str);
char *read_line(void);
void write_prompt(void);
void execute_command(char *command);
int _strcmp(const char *s1, const char *s2);

#endif /* MY_SHELL_H */

