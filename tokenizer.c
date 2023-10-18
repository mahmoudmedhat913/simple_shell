#include "shell.h"

/**
 * **strtow - split string to words
 * @str: string
 * @s: string
 * Return: pointer
 */

char **strtow(char *str, char *s)
{
	char **c;
	int i, j, k, l, num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!s)
		s = " ";
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isdelim(str[i], s) && (isdelim(str[i + 1], s)
					|| !str[i + 1]))
			num++;
	}
	if (num == 0)
		return (NULL);
	c = malloc((1 + num) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (isdelim(str[i], s))
			i++;
		k = 0;
		while (!isdelim(str[i + k], s) && str[i + k])
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			c[j][l] = str[i++];
		c[j][l] = 0;
	}
	c[j] = NULL;
	return (c);
}




/**
 * **strtow2 - split string to words
 * @str: string
 * @s: string
 * Return: pointer
 */

char **strtow2(char *str, char s)
{
	char **c;
	int i, j, k, l, num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != s && str[i + 1] == s) ||
					(str[i] != s && !str[i + 1]) ||
					str[i + 1] == s)
		{
			num++;
		}
	}
	if (num == 0)
		return (NULL);
	c = malloc((1 + num) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (str[i] == s && str[i] != s)
			i++;
		k = 0;
		while (str[i + k] != s && str[i + k] && str[i + k] != s)
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			c[j][l] = str[i++];
		c[j][l] = 0;
	}
	c[j] = NULL;
	return (c);
}
