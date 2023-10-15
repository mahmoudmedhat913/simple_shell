#include "shell.h"

/**
 * bfree - free pointer
 * @n: addres
 * Return: 1 or 0 for fail
 */

int bfree(void **n)
{
	if (n && *n)
	{
		free(*n);
		*n = NULL;
		return (1);
	}
	return (0);
}
