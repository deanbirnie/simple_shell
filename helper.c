#include "shell.h"

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_ctrld(char **args);


/*
 * List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {"cd", "help", "exit", "^D"};

int (*builtin_func[]) (char **) = {&shell_cd,
				   &shell_help, &shell_exit, &shell_ctrld};


/**
 * num_builtins - returns the number of built-in functions.
 * Return: The number of built-in functions.
 */
int num_builtins(void)
{
	return (sizeof(builtin_str) / sizeof(char *));
}

/**
 *_fork - creates a child process and executes the command.
 *@arg: list of arguments passed to the function.
 *@av: list of arguments passed to the program.
 *@env: list of environment variables.
 *@lineptr: pointer to the input buffer.
 *@np: line number in the script file.
 *@c: flag to indicate whether the command is executed in the main process.
 *Return: The status of the child process.
 */
int _fork(char **arg, char **av, char **env, char *lineptr, int np, int c)
{
	pid_t child;
	int status, i = 0;
	char *format = "%s: %d: %s: not found\n";

	if (arg[0] == NULL)
		return (1);
	for (i = 0; i < num_builtins(); i++)
	{
		if (_strcmp(arg[0], builtin_str[i]) == 0)
			return (builtin_func[i](arg));
	}

	child = fork();
	if (child == 0)
	{
		if (execve(arg[0], arg, env) == -1)
		{
			fprintf(stderr, format, av[0], np, arg[0]);
			if (!c)
				free(arg[0]);
			free(arg);
			free(lineptr);
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		return (status);
	}

	return (0);
}

/**
 *shell_cd - changes the current working directory.
 *@args: list of arguments passed to the function.
 *Return: Always returns 1.
 */
int shell_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "hsh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("hsh");
		}
	}

	return (1);
}

/**
 *shell_help - displays the help information.
 *@args: list of arguments passed to the function.
 *Return: Always returns 1.
 */
int shell_help(char **args)
{
	int i;

	printf("man");
	printf("If help call, man\n");
	(void) args;
	for (i = 0; i < num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	return (1);
}

/**
 *shell_exit - exits the shell.
 *@args: list of arguments passed to the function.
 *Return: Always returns 200.
 */
int shell_exit(char **args)
{
	(void) args;
	free(args);
	return (200);
}

/**
 *shell_ctrld - exits the shell when ^D is entered.
 *@args: list of arguments passed to the function.
 *Return: Always returns 200.
 */
int shell_ctrld(char **args)
{
	(void) args;
	free(args);
	return (200);
}
