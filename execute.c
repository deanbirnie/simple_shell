#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "shell.h"

/**
 *execute - executes a command
 *@args: the command to execute
 *@env: environment variables
 *
 *Return: On success, return 0. On failure, return an error code.
 */
int execute(char **args, char **env)
{
	struct stat st;
	char *path = NULL, **tokens = NULL;
	pid_t pid;

	path = find_path(args[0]);
	if (path == NULL)
		return (-1);

	if (stat(path, &st) != 0 || !(st.st_mode &S_IXUSR))
	{
		free(path);
		return (-1);
	}

	tokens = tokenize(args[0], ":");

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}

	if (pid == 0)
	{
		execve(path, args, env);
		perror("Error");
		exit(EXIT_FAILURE);
	}

	wait(NULL);

	free(path);
	free(tokens);
	return (0);
}

/**
 *find_path - finds the full path of a command
 *@command: the command to find the full path of
 *
 *Return: On success, return the full path of the command. On failure, return NULL.
 */
char *find_path(char *command)
{
	char *path = NULL, **tokens = NULL, *full_path = NULL;
	int i = 0;

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);

	tokens = tokenize(path, ":");
	free(path);

	while (tokens[i] != NULL)
	{
		full_path = malloc(sizeof(char) *(_strlen(tokens[i]) + _strlen(command) + 2));
		if (full_path == NULL)
		{
			free(tokens);
			return (NULL);
		}

		_strcpy(full_path, tokens[i]);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) &&
			(st.st_mode &S_IXUSR))
		{
			free(tokens);
			return (full_path);
		}

		free(full_path);
		i++;
	}

	free(tokens);
	return (NULL);
}
