#include "shell.h"

/**
 * *__memset - fill memory with a byte
 * @n: pointer
 * @byte: byte
 * @c: amount of filled bytes
 * Return: pointer
 */

char *__memset(char *n, char byte, unsigned int c)
{
	unsigned int i;

	for (i = 0; i < c; i++)
	{
		n[i] = byte;
	}
	return (n);
}

/**
 * ffree - free string
 * @str: string
 */

void ffree(char **str)
{
	char **s = str;

	if (!str)
		return;
	while (*str)
	{
		free(*str++);
	}
	free(s);
}




/**
 * *__realloc - reallocate block of memory
 * @n: pointer
 * @old: old size
 * @new: new size
 * Return: pointer
 */

void *__realloc(void *n, unsigned int old, unsigned int new)
{
	char *s;

	if (!n)
		return (malloc(new));
	if (!new)
		return (free(n), NULL);
	if (new == old)
		return (n);
	s = malloc(new);
	if (!s)
		return (NULL);
	old = old < new ? old : new;
	while (old--)
		s[old] = ((char *)n)[old];
	free(n);
	return (s);
}
