#include "shell.h"

/**
 * _strchr - searches for the first occurance of a specified character
 *
 * @str: the string in which it will search for the character
 * @c: the character to be searched for
 *
 * Return: pointer to the character in the string or NULL if the character
 * cannot be found
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0' && *str != c)
	{
		str++;
	}
	if (*str == c)
	{
		return ((char *)str);
	}
	return (NULL);
}

/**
 * _strtok - breaks down a string into smaller strings according to
 * the specified delimiter each time it is called
 *
 * @str: the string to be tokenised
 * @delim: the delimter to use to split up the string
 *
 * Description: It is a good idea to create a copy of your string before
 * calling _strtok as _strtok will modify the string in it's existing memory
 * location. The first time you call _strtok you must pass both the string and
 * the delimter (i.e. _strtok(str, delim)). Each time _strtok is called
 * thereafter, use NULL instead of the string (i.e. _strtok(NULL, delim))
 * because it stores it's position in the string using a static variable
 * which persist between function exits.
 *
 * Return: a pointer to the token or the start of an array of strings
 */
char *_strtok(char *str, const char *delim)
{
	static char *last;
	char *start;

	if (str != NULL)
	{
		last = str;
	}
	else
	{
		if (last == NULL)
		{
			return (NULL);
		}
		str = last;
	}
	while (*str != '\0' && _strchr(delim, *str) != NULL)
	{
		str++;
	}
	if (*str == '\0')
	{
		return (NULL);
	}
	start = str;
	while (*str != '\0' && _strchr(delim, *str) == NULL)
	{
		str++;
	}
	if (*str != '\0')
	{
		*str = '\0';
		last = str + 1;
	}
	else
	{
		last = NULL;
	}

	return (start);
}

/**
 * _strlen - returns length of string
 *
 * @s: string
 *
 * Return: length of string
 */

int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
	{
		len++;
	}

	return (len);
}

/**
 * _strcmp - compare string values
 * @s1: input value
 * @s2: input value
 *
 * Return: s1[i] - s2[i]
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
