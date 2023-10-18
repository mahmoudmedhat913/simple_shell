#include "shell.h"

/**
 * active - returns treu if shell inter
 * @info: struct address
 *
 * Return: 1 or 0 for fail
 */
int active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->fdread <= 2);
}

/**
 * isdelim - see if character is a delimeter
 * @c: character
 * @d: string
 * Return: 1 or 0 for fail
 */
int isdelim(char c, char *d)
{
	while (*d)
	{
		if (*d++ == c)
			return (1);
	}
	return (0);
}

/**
 * isalpha - check for alphabet char
 * @c: character
 * Return: 1 or 0 for fail
 */
int isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an int
 * @str: string
 * Return: converted no.
 */

int _atoi(char *str)
{
	int i, sign = 1, f = 0, conv;
	unsigned int res = 0;

	for (i = 0; str[i] != '\0' && f != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			f = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sign == -1)
		conv = -res;
	else
		conv = res;

	return (conv);
}
