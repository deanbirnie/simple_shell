#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_CMD_LENGTH 1024

/*Parse the user's input */
void parse_input(char *input, char **args)
{
	char *token;
	int i = 0;

	/*Get the first token */
	token = strtok(input, " \n");

	/*Keep getting tokens until we reach the end of the input */
	while (token != NULL)
	{
		args[i] = token;
		i++;

		/*Get the next token */
		token = strtok(NULL, " \n");
	}

	/*Set the last argument to NULL to mark the end of the argument list */
	args[i] = NULL;
}

/*Execute the command */
void execute(char **args)
{
	pid_t pid;

	/*Fork the process */
	pid = fork();

	if (pid == 0)
	{
		/*Child process */
		if (execvp(args[0], args) == -1)
		{
			perror("Error");
		}

		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/*Forking error */
		perror("Error");
	}
	else
	{
		/*Parent process */
		int wpid;
		do { 	wpid = waitpid(pid, NULL, WUNTRACED);
		}

		while (!WIFEXITED(wpid) && !WIFSIGNALED(wpid));
	}
}

int main(void)
{
	char input[MAX_CMD_LENGTH];
	char *args[MAX_CMD_LENGTH / 2 + 1];

	while (1)
	{
		/*Get user input */
		printf("Shell > ");
		fgets(input, MAX_CMD_LENGTH, stdin);

		/*Parse the input into arguments */
		parse_input(input, args);

		/*Execute the command */
		if (strcmp(args[0], "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			execute(args);
		}
	}

	return (0);
}
