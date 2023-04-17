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

/* Display the prompt for the user to to enter a command */
void prompt();

/* Entry point of the simple shell program */
int main(void);

/* Read the user's input command from standard input */
char *read_input();

/* Handles the execution of processes and child processes */
int execute(char **args);

#endif
