#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>

#define TOKEN_DELIM " \t\r\n\a"
#define INPUT_SIZE 200
#define PATH_SIZE 1024
#define ARG_SIZE 200

typedef struct ShellInfo
{
    int status;
} ShellInfo;

void setExecutableName(char *name);

void display(char *ch, int lent);

ssize_t addInput(char *input);

int runCommandFile(char *command, char *argv, char *envp[]);

void handleCommandExit(int status, const char *command);

void tokenizeCommand(char *command, char **args);

int callUp(char *command, char *args[], char *argv, char **env);

int execWithPath(char *command, char *args[], char **env);

void exitShell(int status);

int chkCmdBeforeFork(char *command);

int tokenizeCommand(char *command, char *args[]);

char *sStrdup(const char *string);

int sStrlen(const char *string);

int sStrcspn(const char *string, const char *chr);

char *sStrcpy(char *destString, const char *srcString);

char *sStrchr(const char *string, int chr);

char *sStrcat(char *dest, const char *src);

int sStrcmp(const char *str1, const char *str2);

char *sStrstr(const char *haystack, const char *needle);

int sStrncmp(const char *s1, const char *s2, size_t n);

char *sStrtok(char *str, const char *delim);

int isDelimiter(char ch, const char *delim);

char *sGetenv(const char *string, char *envp[]);

int sepCmd(const char *command, char *outcome[], int num);

char *handleDoubleDollar(const char *cmd, char *envp[]);

void disableComment(char *cmd);

int getStatusCode(int status);

void intToString(int value, char *str, int size);

int executeCommand(char *args[], int check, int *status,
                    char *argv, char *envp[]);

void replaceStatusVariable(char *args[], int count, int *status);

int logicalOperator(char *input, const char *delimiter,
                    char *result[]);

void removeQuote(char *input, char *result);

void signalHandler(int signal);

int checkCmd(char *mycmd);

char *itoa(int num);

void assignLinePtr(char **lineptr, size_t *n, char *buffer, size_t b);

ssize_t sGetline(char **lineptr, size_t *n, FILE *stream);

void *sRealloc(void *ptr, unsigned int oldSize, unsigned int newSize);

int isWhitespace(char ch);
int isWordStart(char *str, int number);

char *handleDoubleDollars(char *cmd, char *envp[]);
void handleEnvironmentVariable(char *cmd, char *result, int *i,
                               int *b, char *envp[]);
void handleDoubleDollarInternal(char *cmd, char *result, int *i, int *j);
char *getEnvironmentVariableValue(char *varName, char *envp[]);
char *getProcessIdString();
int sIsalnum(unsigned char c);
char *sStrndup(char *source, size_t n);

void logicalCommands(char *copy, char *args[], int check,
                     int *status, char *argv, char *envp[]);
int whitespace(char *str);
int runCommand(char *command, char *argv, char *envp[]);

void intToString(int num, char *str, int strSize);
void printError(const char *command, char *argv);

#endif

