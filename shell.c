#include "shell.h"

/**
 * main - Simple Shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input = NULL;
	size_t input_len = 0;
	ssize_t read_len = 0;
	char *tokens[MAX_TOKENS];
	int num_tokens = 0, i = 0;

	while (1)
	{
		printf("$ ");
		read_len = getline(&input, &input_len, stdin);
		if (read_len == -1;
		{
			perror("Error");
			break;
		}
		if (read_len == 1)
		{
			continue;
		}
		input[read_len - 1] = '\0';
		tokenize_input(input, tokens, &num_tokens);
		if (strcmp(tokens[0], "exit") == 0)
		{
			handle_exit();
		}
		else if (strcmp(tokens[0], "cd") == 0)
		{
			if (num_tokens < 2)
			{
				fprintf(stderr, "cd: missing argument\n");
				continue;
			{
				handle_cd(tokens[1]);
			}
			else
			{
				pid_t pid = fork();

				if (pid == -1)
				{
					perror("Error");
				}
				else if (pid == 0)
				{
					execvp(tokens[0], tokens);
					perror("Error");
					exit(EXIT_FAILURE);
				}
				else
				{
					waitpid(pid, &i, 0);
				}
			}
			}
			free(input);
			return (0);
		}

/**
 * tokenize_input - Tokenize the input
 * @input: Input string
 * @tokens: Array to store the tokens
 * @num_tokens: Number of tokens
 *
 * Return: void
 */
void tokenize_input(char *input, char **tokens, int *num_tokens)
{
	char *token;

	*num_tokens = 0;
	token = strtok(input, " \n\t\r");
	while (token != NULL && *num_tokens < MAX_TOKENS)
	{
		tokens[*num_tokens] = token;
		*num_tokens += 1;
		token = strtok(NULL, " \n\t\r");
	}
	tokens[*num_tokens] = NULL;
}

/**
 * handle_cd - Change the current directory
 * @path: Path of the directory
 *
 * Return: void
 */
void handle_cd(char *path)
{
	if (chdir(path) == -1)
	{
		perror("Error");
	}
}

/**
 * handle_exit - Exit the shell
 *
 * Return: void
 */
void handle_exit(void)
{
	exit(EXIT_SUCCESS);
}
