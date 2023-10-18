#include "shell.h"

/**
 * history - display the history list
 * @info: param struct
 * Return: 0
 */
int history(info_t *info)
{
	printlist(info->history);
	return (0);
}

/**
 * unsetalias - set alias to string
 * @info: Param strut
 * @str: string
 *
 * Return: 0 or 1 for fail
 */
int unsetalias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _stringchr(str, "=");
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deletenode(&(info->alias),
			nodeindex(info->alias, nodestart(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setalias - set alias to string
 * @info: param struct
 * @str: string
 *
 * Return: Always 0 on succ, 1 on err
 */
int setalias(info_t *info, char *str)
{
	char *p;

	p = _stringchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetalias(info, str));

	unsetalias(info, str);
	return (addendnode(&(info->alias), str, 0) == NULL);
}

/**
 * printalias - print alias string
 * @n: alias node
 *
 * Return: Always 0 on suc, on err
 */
int printalias(list_t *n)
{
	char *p = NULL, *s = NULL;

	if (n)
	{
		p = _stringchr(n->str, '=');
		for (s = n->str; s <= p; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias - mimic alias builtin
 * @info: param struct
 * Return: 0
 */
int alias(info_t *info)
{
	int i = 0;
	char *s = NULL;
	list_t *n = NULL;

	if (info->argc == 1)
	{
		n = info->alias;
		while (n)
		{
			printalias(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		s = _stringchr(info->argv[i], '=');
		if (s)
			setalias(info, info->argv[i]);
		else
			printalias(nodestart(info->alias, info->argv[i], '='));
	}

	return (0);
}
