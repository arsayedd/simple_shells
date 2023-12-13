#ifndef _SHELL_H_
#define _SHELL_H_

#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "custom_types.h"      
#include "custom_constants.h"

/* global environment */
extern char **environ;
/* global program name */
char *name;
/* global aliases linked list */
alias_t *aliases;

/* signals and processes */
void signal_handler(int);

/* helpers for user inputs */
char *get_user_input();

/* helpers errors handling */
/* 0: readline_error */
void custom_readline_error(void);

void (*handle_error[])(void) = {
    readline_error
};

#endif /* _SHELL_H_ */

