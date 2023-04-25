#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * _getline - takes user's input and stores it for further manipulation
 *
 * @lineptr: the line we want to retrieve, pointer to a pointer to a
 * character buffer
 * @n: size of the buffer
 * @stream: pointer to a file object
 *
 * Return: number of characters read from the input stream or -1 (error)
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t chars_read = 0;
	size_t buffer_size = (*n == 0) ? 128 : *n;
	size_t new_buffer_size;
	char *buffer = *lineptr;
	char *new_buffer;
	int c;

	if (buffer == NULL)
	{
		buffer = malloc(buffer_size);
		if (buffer == NULL)
		{
			return (-1);
		}
	}

	while (1)
	{
		c = _fgetc(stream);

		if (c == EOF)
		{
			if (chars_read == 0)
			{
				return (-1);
			}
			else
			{
				break;
			}
		}

		if (chars_read >= buffer_size - 1)
		{
			new_buffer_size = buffer_size * 2;
			new_buffer = realloc(buffer, new_buffer_size);

			if (new_buffer == NULL)
			{
				free(buffer);
				return (-1);
			}

			buffer = new_buffer;
			buffer_size = new_buffer_size;
			*lineptr = buffer;
		}

		buffer[chars_read] = c;
		chars_read++;

		if (c == '\n')
		{
			break;
		}
	}

	if (chars_read > 0 && buffer[chars_read-1] != '\n')
	{
		new_buffer_size = buffer_size + 1;
		new_buffer = realloc(buffer, new_buffer_size);

		if (new_buffer == NULL)
		{
			free(buffer);
			return (-1);
		}

		buffer = new_buffer;
		buffer_size = new_buffer_size;
		*lineptr = buffer;

		buffer[chars_read] = '\n';
		chars_read++;
		buffer[chars_read] = '\0';
	}
	else
	{
		buffer[chars_read] = '\0';
	}

	*n = buffer_size;
	*lineptr = buffer;

	return (chars_read);
}

/**
 * _fgetc - reads characters from input stream
 *
 * @stream: pointer to the input stream to read from
 *
 * Return: character from input stream
 */
int _fgetc(FILE *stream)
{
	unsigned char c;

	if (_fread(&c, sizeof(c), 1, stream) != 1)
	{
		return (EOF);
	}
	return (c);
}

/**
 * _fread - reads data from a given input stream and stores it in a buffer
 *
 * @ptr: pointer to the buffer where the read data will be stored
 * @size: size of each element to be read
 * @count: number of elements to be read
 * @stream: pointer to the input stream to read from
 *
 * Return: number of complete elements that were read or -1 if it fails or
 * reaches EOF
 */
size_t _fread(void *ptr, size_t size, size_t count, FILE *stream)
{
	char *buf_ptr = (char *)ptr;
	size_t bytes_to_read = size * count;
	size_t bytes_read = 0;
	size_t total_bytes_read = 0;
	size_t i;
	size_t bytes_per_read;
	size_t bytes_read_this_time;
	char buffer[BUFSIZ];

	while (bytes_to_read > 0)
	{
		bytes_per_read = (bytes_to_read < BUFSIZ) ? bytes_to_read : BUFSIZ;
		bytes_read_this_time = fread(buffer, 1, bytes_per_read, stream);

		if (bytes_read_this_time == 0)
		{
			if (feof(stream))
			{
				break;
			} else {
				return (-1);
			}
		}

		for (i = 0; i < bytes_read_this_time; i++)
		{
			*buf_ptr = buffer[i];
			buf_ptr++;
			bytes_to_read--;
			bytes_read++;
		}

		total_bytes_read += bytes_read_this_time;
	}

	return (total_bytes_read / size);
}
