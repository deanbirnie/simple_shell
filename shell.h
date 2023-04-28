#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* Function declarations */
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_ctrld(char **args);

extern char **environ;


int _strcmp(char *s1, char *s2);
size_t _strncmp(char *s1, char *s2, size_t n);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _putchar(char c);
int num_builtins(void);
void _exit_command(char **args, char *lineptr, int _exit);
int _fork(char **arg, char **av, char **env, char *lineptr, int np, int c);
char *_getline_command(void);
int v_path(char **arg, char **env);
char *_path(char **env);
void _getenv(char **env);
char **tokenize(char *line);
int is_empty_or_whitespace(const char *str);

#endif
