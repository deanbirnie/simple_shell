#include "shell.h"

/**
 * _getline_command - captures user input and stores it in a buffer
 *
 * Return: pointer to the input string or NULL on failure
 */
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

/**
 * _path - find the PATH environment variable in env array
 *
 * @env: array of strings
 *
 * Return: returns the path for execve() or NULL on failure
 */
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
	path = malloc(sizeof(char) * (count + 1));

	if (path == NULL)
		return (NULL);

	for (var = 5, count = 0; env[index][var];
		var ++, count++)
		path[count] = env[index][var];

	path[count] = '\0';
	return (path);
}

/**
 * _getenv - prints all environment variables to stdout
 *
 * @env: array of strings that represent the environment variables
 * of the current process
 */
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

/**
 * is_empty_or_whitespace - checks if the string contains only whitespace
 * characters
 *
 * @str: pointer to a string which is the input from the user
 *
 * Return: -1 if it contains only whitespace characters or 0 if it does not
 */
int is_empty_or_whitespace(const char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
		{
			return (0);
		}
		str++;
	}
	return (-1);
}
