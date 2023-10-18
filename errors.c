#include "shell.h"

/**
 * _errorputs - print string
 * @str: string
 */
void _errorputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_errorputchar(str[i]);
		i++;
	}
}

/**
 * _errorputchar - write character to stderr
 * @c: character
 * Return: 1 or -1 for fail
 */
int _errorputchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == buffer_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != buffer_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _fdput - write character to given fd
 * @c: character
 * @fd: filedescriptor
 * Return: 1 or -1 for fail
 */
int _fdput(char c, int fd)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == buffer_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != buffer_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _fdputs - get input string
 * @str: string
 * @fd: filedescriptor
 *
 * Return: the number of characters
 */
int _fdputs(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _fdput(*str++, fd);
	}
	return (i);
}
