#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/* Define the maximum size of a command input */
#define BUFFER_SIZE 1024

/* Display the prompt for the user to enter a command */
void prompt(void)
{
	printf("> ");
}

/* Read the user's command input from standard input */
	char *read_input()
{
/* Allocate memory for the input string */
	char *input = (char *) malloc(BUFFER_SIZE * sizeof(char));

/* Read upto BUFFER_SIZE characters from standard input,store them in input */
	   fgets(input, BUFFER_SIZE, stdin);

	   /* Return the input string */
	   return (input);
}

/* The main function of the shell */
int main(void)
{
	char *input;    /* A string to hold the user's input command */
	char **args;    /* An array to hold the arguments of the command */
	int status;     /* The exit status of the command */

	/* Loop until the shell is exited */
	while (1)
	{
		/* Display the prompt */
		prompt();

		/* Read the user's command input */
		input = read_input();

		 /* If the end of file (Ctrl+D) is reached, exit the shell */
                if (input == NULL) 
		{
                    printf("\n");
                    break;
                }

		/* Parse the input string into an array of arguments */
		args = parse_input(input);

/* execute(args) function takes an array of command-line arguments as input */
		status = execute(args);

		/* Free the memory allocated for the input and arguments */
		free(input);
		free(args);

		/* Check if the shell should be exited */
		if (status == EXIT_SHELL)
		{
			break;
		}
	}

	/* Exit the shell */
	return (0);
}

