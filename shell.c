#include "shell.h"

/**
 *main - entry point for the shell
 *Return: Always 0 on success.
 */
int main(void)
{
	char *input = NULL;
	size_t input_len = 0;
	ssize_t read_len = 0;
	char *tokens[MAX_TOKENS];
	int num_tokens = 0
		;
	while (1)
	{
		printf("$ ");
		read_len = getline(&input, &input_len, stdin);
		if (read_len == -1)
	{
		perror("getline failed");
		continue;
	}
		if (read_len == 1)
	{
		continue;
	}
	tokenize_input(input, tokens, &num_tokens);
	if (strcmp(tokens[0], "cd") == 0)
	{
		if (num_tokens < 2)
	{
		fprintf(stderr, "cd: missing argument\n");
		continue;
	}
		handle_cd(tokens[1]);
	}
	else if (strcmp(tokens[0], "exit") == 0)
	{
		handle_exit();
	}	else
	{
		execute_command(tokens);
	}
}
	free(input);
	input = NULL;
	return (0);
}
