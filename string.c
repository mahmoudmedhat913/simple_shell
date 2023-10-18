#include "shell.h"

/**
 * _strlen - return length of string
 * @str: string
 * Return: length
 */

int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str++)
	{
		i++;
	}
	return (i);
}

/**
 * _strcmp - compare 2 strings
 * @str1: string
 * @str2: string
 * Return: 1 if str1>str2 or -1 if str1<str2 or 0 if equal
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * *startwith - see if needle start with haystack
 * @haystack: string
 * @needle: string
 * Return: address
 */

char *startwith(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}

/**
 * *_strcat - concatenate 2 strings
 * @dest: buffer
 * @source: buffer
 * Return: pointer
 */

char *_strcat(char *dest, char *source)
{
	char *x = dest;

	while (*dest)
	{
		dest++;
	}
	while (*source)
	{
		*dest++ = *source++;
	}
	*dest = *source;
	return (x);
}
