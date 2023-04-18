#include "shell.h" 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <errno.h>

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
			{	/* permission denied */
				return (PERMISSION_DENIED);
			}
			else
			{	/* other error */
				perror("execvp");
				return (EXECUTION_ERROR);
			}
		}
		exit(EXIT_FAILURE); /* exit the child process */
    }
    else if (pid < 0)
	{	/* error forking */
		perror("fork");
		return (FORK_ERROR);
	}
	else
	{	/* parent process */
		do 
		{
		/* wait for child process to terminate */
		waitpid(pid, &status, WUNTRACED);
		}
		/* loop until child process exits or is terminated */
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (0); /* return exit status of the child process */
}
