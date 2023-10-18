#include "shell.h"

/**
 * listlength - see the length of list
 * @h: address to head
 * Return: length
 */

size_t listlength(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * **listtostring - return array of strings
 * @h: address to head
 * Return: array of strings
 */

char **listtostring(list_t *h)
{
	list_t *n = h;
	size_t i = listlength(h), j;
	char **s, *str;

	if (!h || !i)
		return (NULL);
	s = malloc(sizeof(char *) * (i + 1));
	if (!s)
		return (NULL);
	for (i = 0; n; n = n->next, i++)
	{
		str = malloc(sizeof(n->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
			{
				free(s[j]);
			}
			free(s);
			return (NULL);
		}
		str = _strcpy(str, n->str);
		s[i] = str;
	}
	s[i] = NULL;
	return (s);
}

/**
 * printlist - print list
 * @h: address to head
 * Return: size
 */

size_t printlist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convertnum(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * *nodestart - gives node that string start with prefix
 * @h: address to head
 * @str: string
 * @c: character
 * Return: the matched node or null
 */

list_t *nodestart(list_t *h, char *str, char c)
{
	char *p = NULL;

	while (h)
	{
		p = startwith(h->str, str);
		if (p && ((c == -1) || (*p == c)))
			return (h);
		h = h->next;
	}
	return (NULL);
}

/**
 * nodeindex - get node index
 * @h: address to head
 * @n: address to node
 * Return: index or -1
 */

ssize_t nodeindex(list_t *h, list_t *n)
{
	size_t i = 0;

	while (h)
	{
		if (h == n)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
