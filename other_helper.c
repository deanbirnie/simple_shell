/*other_helper.c */ 
#include "shell.h"

char *_getline_command(void)
{
	char *lineptr = NULL;
	size_t charter_user = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	if (getline(&lineptr, &charter_user, stdin) == -1)
	{
		free(lineptr);
		return (NULL);
	}

	return (lineptr);
}

char *_path(char **env)
{
	size_t index = 0,
		var = 0, count = 5;
	char *path = NULL;

	for (index = 0; _strncmp(env[index], "PATH=", 5); index++)
	;
	if (env[index] == NULL)
		return (NULL);

	for (count = 5; env[index][var];
		var ++, count++)
	;
	path = malloc(sizeof(char) *(count + 1));

	if (path == NULL)
		return (NULL);

	for (var = 5, count = 0; env[index][var];
		var ++, count++)
		path[count] = env[index][var];

	path[count] = '\0';
	return (path);
}

void _getenv(char **env)
{
	size_t run = 0;

	while (env[run])
	{
		write(STDOUT_FILENO, env[run], _strlen(env[run]));
		write(STDOUT_FILENO, "\n", 1);
		run++;
	}
}
