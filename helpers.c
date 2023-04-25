#include "shell.h"

/**
 * handle_cd - change the current working directory to the specified path
 * @path: path to the directory to change to
 *
 * This function uses the chdir() system call to change the current working
 * directory to the directory specified by the `path` argument. If the
 * chdir() call fails, an error message is printed using perror().
 */
void handle_cd(char *path)
{
	if (chdir(path) != 0)
	{
		perror("chdir failed");
	}
}

/**
 * handle_exit - exit the shell
 *
 * This function terminates the shell process by calling the exit() function
 * with the EXIT_SUCCESS status code.
 */
void handle_exit(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * execute_command - execute a command with the specified arguments
 * @tokens: array of strings representing the command and its arguments
 *
 * This function executes the specified command and its arguments in a new
 * process using the execvp() system call. It waits for the child process to
 * complete using waitpid(), and returns its exit status. If an error occurs,
 * the function returns -1 and prints an error message using perror().
 *
 * Return: The exit status of the child process, or -1 on error.
 */
int execute_command(char **tokens)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
		return (-1);
	}
	if (pid == 0)
	{
		execvp(tokens[0], tokens);
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
else
	{
		int status;

		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}

/**
 * tokenize_input - tokenize a string into an array of tokens
 * @input: a string to be tokenized
 * @tokens: an array of strings to store the resulting tokens
 * @num_tokens: a pointer to an integer to store the number of tokens
 *
 * This function uses the _strtok() function to split the input string into
 * tokens, which are stored in the `tokens` array. The maximum number of
 * tokens that can be stored is defined by the MAX_TOKENS macro. The number
 * of tokens is stored in the `num_tokens` variable.
 */
void tokenize_input(char *input, char **tokens, int *num_tokens)
{
	char *token = _strtok(input, " \t\n");
	*num_tokens = 0;
	while (token != NULL && *num_tokens < MAX_TOKENS)
	{
		tokens[*num_tokens] = token;
		*num_tokens += 1;
		token = _strtok(NULL, " \t\n");
	}
	tokens[*num_tokens] = NULL;
}
