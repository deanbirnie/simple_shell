#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Defines the maximum size of an input command */
#define BUFFER_SIZE 1024
#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 100

extern char **environ;


void handle_cd(char *path);
void handle_exit(void);
int execute_command(char **tokens);
void tokenize_input(char *input, char **tokens, int *num_tokens);

char *find_command(char *cmd, char *path);

int execute_path(char *cmd, char **args);

int execute_cmd(char *cmd, char **args);

/* do we need this? */
void prompt(void);

/* Handles the execution of processes and child processes */
int execute(char **args);

/* strparse.c */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strchr(const char *str, int c);
char *_strtok(char *str, const char *delim);

/* getline */
size_t _fread(void *ptr, size_t size, size_t count, FILE *stream);
int _fgetc(FILE *stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif
