#include "shell.h" 
#include <stdio.h> /* include standard input/output library  */
#include <unistd.h> /* include library for POSIX operating system API  */
#include <sys/wait.h> /*  include library for waitpid() system call  */
#include <errno.h> /* include library for error handling  */

/**
 * execute - creates a child process to execute a given command
 *
 * @args: array of arguments including the command to be executed
 *
 * Return: exit status of the child process
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork(); /* create a child process */

	if (pid == 0)
	{
		/* child process */
		if (execvp(args[0], args) == -1)
		{
			/* handle errors that occur during execution */
			if (errno == ENOENT)
			{
				/* command not found */
				return (COMMAND_NOT_FOUND);
			}
			else if (errno == E2BIG)
			{
				/* too many arguments */
				return (TOO_MANY_ARGUMENTS);
			}
			else if (errno == EACCES)
			{
				/* permission denied */
				return (PERMISSION_DENIED);
			}
			else
			{
				/* other error */
				perror("execvp");
				return (EXECUTION_ERROR);
			}
		}
		exit(EXIT_FAILURE); /* exit the child process */
    }
    else if (pid < 0)
    {
        /* error forking */
        /* add your code here */
    }
    else
    {
        /* parent process */
        /* add your code here */
    }

    return (0);
}

