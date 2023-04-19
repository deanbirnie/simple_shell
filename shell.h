#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

/* Defines the maximum size of an input command */
#define BUFFER_SIZE 1024

/* do we need this? */
void prompt(void);

/* Handles the execution of processes and child processes */
int execute(char **args);

/* used by _strtok to find delimters in a given string */
char *_strchr(const char *str, int c);

/* used to parse and separate input commands */
char *_strtok(char *str, const char *delim);

#endif
