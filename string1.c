#include "shell.h"

/**
 * *_strcpy - copy string
 * @dest: destination
 * @source: source
 * Return: pointer
 */

char *_strcpy(char *dest, char *source)
{
	int i = 0;

	if (dest == source || source == 0)
		return (dest);
	while (source[i])
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * *_strdup - duplicate string
 * @str: string
 * Return: pointer
 */

char *_strdup(const char *str)
{
	int l = 0;
	char *x;

	if (str == NULL)
		return (NULL);
	while (*str++)
	{
		l++;
	}
	x = malloc(sizeof(char) * (l + 1));
	if (!x)
		return (NULL);
	for (l++; l--;)
	{
		x[l] = *--str;
	}
	return (x);
}

/**
 * _puts - print string
 * @str: string
 * Return: void
 */

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - write character to stdout
 * @c: character
 * Return: 1
 */

int _putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
	{
		buffer[i++] = c;
	}
	return (1);
}
