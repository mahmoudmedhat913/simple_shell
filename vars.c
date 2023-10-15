#include "shell.h"

/**
 * ischain - see if char is chain delimeter
 * @info: param struct
 * @buffer: char
 * @n: address
 * Return: 1 or 0 for fail
 */

int ischain(info_t *info, char *buffer, size_t *n)
{
	size_t i = *n;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		info->cmdbuffertype = CMD_OR;
	}
	else if (buffer == '&' &&  buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info->cmdbuffertype = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		info->cmdbuffertype = CMD_CHAIN;
	}
	else
		return (0);
	*n = i;
	return (i);
}

/**
 * checkchain - check to continue chaining
 * @info: param struct
 * @buffer: char
 * @n: address
 * @start: integer
 * @l: integer
 * Return: void
 */

void checkchain(info_t *info, char *buffer, size_t *n, size_t start, size_t l)
{
	size_t i = *n;

	if (info->cmdbuffertype == CMD_OR)
	{
		if (!info->status)
		{
			buffer[start] = 0;
			i = l;
		}
	}
	if (info->cmdbuffertype == CMD_AND)
	{
		if (info->status)
		{
			buffer[start] = 0;
			i = l;
		}
	}
	*n = i;
}

/**
 * changealias - change alias
 * @info: param struct
 * Return: 1 or  0 for fail
 */

int changealias(info_t *info)
{
	int i;
	char *s;
	list_t *n;

	for (i = 0; i < 10; i++)
	{
		n = nodestart(info->alias, info->argv[0], '=');
		if (!n)
			return (0);
		free(info->argv[0]);
		s = _stringchr(n->str, '=');
		if (!s)
			return (0);
		s = _strdup(s + 1);
		if (!s)
			return (0);
		info->argv[0] = s;
	}
	return (1);
}

/**
 * changevars - change vars
 * @info: param struct
 * Return: 1 or  0 for fail
 */

int changevars(info_t *info)
{
	int i;
	list_t *n;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			changestring(&(info->argv[i]),
					_strdup(convertnum(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			changestring(&(info->argv[i]),
					_strdup(convertnum(getpid(), 10, 0)));
			continue;
		}
		n = nodestart(info->env, &info->argv[i][1], '=');
		if (n)
		{
			changestring(&(info->argv[i]),
					_strdup(_stringchr(n->str, '=') + 1));
			continue;
		}
		changestring(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * changestring - change string
 * @s: address of old string
 * @c: new string
 * Return: 1 or 0 for fail
 */

int changestring(char **s, char *c)
{
	free(*s);
	*s = c;
	return (1);
}
