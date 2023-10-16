#include "shell.h"

/**
 * *addnode - add a node
 * @h: address to head
 * @s: string
 * @i: index
 * Return: size
 */

list_t *addnode(list_t **h, const char *s, int i)
{
	list_t new;

	if (!h)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	memset((void *)new, 0, sizeof(list_t));
	new->num = i;
	if (s)
	{
		new->str = _strdup(s);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *h;
	*h = new;
	return (new);
}

/**
 * *addendnode - add node at the end
 * @h: address to head
 * @s: string
 * @i: index
 * Return: size
 */

list_t addendnode(list_t **h, const char *s, int i)
{
	list_t *n, *new;

	if (!h)
		return (NULL);
	n = *h;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	memset((void *)new, 0, sizeof(list_t));
	new->num = i;
	if (s)
	{
		new->str = _strdup(s);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
		{
			n = n->next;
		}
		n->next = new;
	}
	else
		*h = new;
	return (new);
}

/**
 * printstringlist - print string
 * @h: address to head
 * Return: size
 */

size_t printstringlist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * deletenode - delete a node
 * @h: address to head
 * @i: index
 * Return: 1 or 0 for fail
 */

int deletenode(list_t **h, unsigned int i)
{
	list_t *n, *p;
	unsigned int j = 0;

	if (!h || !*h)
		return (0);
	if (!i)
	{
		n = *h;
		*h = (*h)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *h;
	while (n)
	{
		if (j == i)
		{
			p->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		j++;
		p = n;
		n = n->next;
	}
	return (0);
}

/**
 * freelist - free all nodes
 * @h: address to head
 */

void freelist(list_h **h)
{
	list_t *next, *n, *p;

	if (!h || !*h)
		return;
	p = *h;
	n = p;
	while (n)
	{
		next = n->next;
		free(n->str);
		free(n);
		n = next;
	}
	*h = NULL;
}
