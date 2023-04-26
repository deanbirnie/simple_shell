#include "shell.h"

/**
 *tokenize - Tokenize a string
 *@lineptr: String to tokenize
 *
 *Return: An array of tokens
 */
char **tokenize(char *lineptr)
{
	char **user_command = NULL;
	char *token = NULL;
	size_t i = 0;
	int size = 0;

	if (lineptr == NULL)
		return (NULL);

	for (i = 0; lineptr[i]; i++)
	{
		if (lineptr[i] == ' ')
			size++;
	}

	if ((size + 1) == _strlen(lineptr))
		return (NULL);
	user_command = malloc(sizeof(char *) * (size + 2));
	if (user_command == NULL)
		return (NULL);

	token = strtok(lineptr, " \n\t\r");

	for (i = 0; token != NULL; i++)
	{
		user_command[i] = token;
		token = strtok(NULL, " \n\t\r");
	}

	user_command[i] = NULL;
	return (user_command);
}

/**
 * v_path - Find the path to an executable file
 * @arg: The command to find
 * @env: The environment variables
 *
 * Return: 0 on success, -1 on failure
 */
int v_path(char **arg, char **env)
{
	char *token = NULL, *path_rela = NULL, *path_absol = NULL;
	size_t value_path, len;
	struct stat stat_lineptr;

	if (stat(*arg, &stat_lineptr) == 0)
		return (-1);
	path_rela = _path(env); /**gets the content of "PATH="*/
	if (!path_rela)
		return (-1);
	token = strtok(path_rela, ":"); /**tokenizes the content of "PATH="*/
	len = _strlen(*arg); /**gets length of arg*/
	while (token)
	{
		value_path = _strlen(token);
		path_absol = malloc(sizeof(char) * (value_path + len + 2));
		if (!path_absol)
		{
			free(path_rela);
			return (-1);
		}

		path_absol = strcpy(path_absol, token);
		_strcat(path_absol, "/");
		_strcat(path_absol, *arg);

		if (stat(path_absol, &stat_lineptr) == 0)
		{ *arg = path_absol;
			free(path_rela);
			return (0);
		}

		free(path_absol);
		token = strtok(NULL, ":");
	}

	token = '\0';
	free(path_rela);
	return (-1);
}
