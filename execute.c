#include "shell.h"

/**
 *execute - executes a command with arguments
 *@args: array of arguments passed to command
 *Return: status code of command
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/*Child process */
		if (execve(args[0], args, environ) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		/*Error forking */
		perror("Error");
	}
	else
	{
		/*Parent process */
		do {	status = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (status);
}

/**
 *find_command - finds a command in PATH
 *@cmd: command to find
 *@path: buffer to store path in
 *Return: pointer to path or NULL if command not found
 */
char *find_command(char *cmd, char *path)
{
	char *dir, *p;
	struct stat st;

	p = _strtok(path, ":");
	while (p)
	{
		dir = malloc(strlen(p) + strlen(cmd) + 2);
		if (!dir)
			exit(EXIT_FAILURE);

		sprintf(dir, "%s/%s", p, cmd);
		if (stat(dir, &st) == 0)
			return (dir);

		free(dir);
		p = _strtok(NULL, ":");
	}

	return (NULL);
}

/**
 *get_path - gets the PATH environment variable
 *Return: pointer to PATH or NULL if not found
 */
char *get_path(void)
{
	char *path = getenv("PATH");

	if (!path)
	{
		perror("Error");
		return (NULL);
	}

	return (path);
}

/**
 *execute_path - executes a command in PATH
 *@cmd: command to execute
 *@args: arguments to pass to command
 *Return: status code of command
 */
int execute_path(char *cmd, char **args)
{
	char *path, *full_path;
	int status;

	path = get_path();
	if (!path)
		return (EXIT_FAILURE);

	full_path = find_command(cmd, path);
	free(path);
	if (!full_path)
	{
		printf("%s: command not found\n", cmd);
		return (EXIT_FAILURE);
	}

	args[0] = full_path;
	status = execute(args);
	free(full_path);

	return (status);
}

/**
 *execute_cmd - executes a command
 *@cmd: command to execute
 *@args: arguments to pass to command
 *Return: status code of command
 */
int execute_cmd(char *cmd, char **args)
{
	int status;

	/*Check if the command is a built-in command */
	if (strcmp(cmd, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(cmd, "cd") == 0)
	{
		if (args[1])
		{
			if (chdir(args[1]) != 0)
			{
				perror("Error");
			}
		}
		else
		{
			chdir(getenv("HOME"));
		}

		return (EXIT_SUCCESS);
	}

	/*If the command is not a built-in command, execute it */
	if (strchr(cmd, '/') != NULL)
	{
		status = execute(args);
	}
	else
	{
		status = execute_path(cmd, args);
	}

	return (status);
}
