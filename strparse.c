/*strparse.c*/ 
#include "shell.h"

/**
 *_strcat - Concatenates two strings.
 *
 *@dest: Pointer to destination string.
 *@src: Pointer to source string.
 *
 *Return: Pointer to concatenated string.
 */
char *_strcat(char *dest, char *src)
{
	int i, j = 0;

	for (i = 0; dest[i] != '\0'; i++) {}

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 *_strcmp - Compares two strings.
 *
 *@s1: Pointer to first string.
 *@s2: Pointer to second string.
 *
 *Return: Integer indicating result of comparison.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int val;

	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
		i++;
	val = s1[i] - s2[i];
	return (val);
}

/**
 *_strlen - Calculates the length of a string.
 *
 *@s: Pointer to string.
 *
 *Return: Length of string.
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++)
	;

	return (i);
}

/**
 *_strncmp - Compares two strings up to a specified number of characters.
 *
 *@s1: Pointer to first string.
 *@s2: Pointer to second string.
 *@n: Number of characters to compare.
 *
 *Return: Integer indicating result of comparison.
 */
size_t _strncmp(char *s1, char *s2, size_t n)
{
	size_t i, j;

	for (j = 0; s1[j] != '\0' && j < n; j++)
	{
		i = s1[j] - s2[j];

		if (i != 0)
		{
			return (i);
		}
	}

	return (0);
}

/**
 *_strcpy - Copies a string from source to destination.
 *
 *@dest: Pointer to destination string.
 *@src: Pointer to source string.
 *
 *Return: Pointer to destination string.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i + 1] = 0;
	return (dest);
}
