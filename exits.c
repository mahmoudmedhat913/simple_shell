#include "shell.h"

/**
 * *_stringcpy - copy string
 * @dest: destination
 * @source: source
 * @num: the ammount of chars
 * Return: concatenated string
 */
char *_stringcpy(char *dest, char *source, int num)
{
	int i, j;
	char *str = dest;

	i = 0;
	while (source[i] != '\0' && i < num - 1)
	{
		dest[i] = source[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 * *_stringcat - concatenate two strings
 * @first: first string
 * @second: second string
 * @num: amount of bytes
 * Return: string
 */
char *_stringcat(char *first, char *second, int num)
{
	int i, j;
	char *str = first;

	i = 0;
	j = 0;
	while (first[i] != '\0')
		i++;
	while (second[j] != '\0' && j < num)
	{
		first[i] = second[j];
		i++;
		j++;
	}
	if (j < num)
		first[i] = '\0';
	return (str);
}

/**
 * *_stringchr - locate character
 * @str: string
 * @c: character
 * Return: pointer
 */
char *_stringchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
