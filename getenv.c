#include "shell.h"

/**
 * **getenviron - return string copy of eniron
 * @info: param struct
 * Return: 0
 */

char **getenviron(info_t *info)
{
	if (!info->environ || info->changedenv)
	{
		info->environ = listtostring(info->env);
		info->changedenv = 0;
	}
	return (info->environ);
}

/**
 * unsetenviron - delete enviroment
 * @info: param struct
 * @st: string
 * Return: 1 or  0 for fail
 */

int unsetenviron(info_t *info, char *st)
{
	char *s;
	size_t i = 0;
	list_t *n = info->env;

	if (!n || !st)
		return (0);
	while (n)
	{
		s = startwith(n->str, st);
		if (s && *s == '=')
		{
			info->changedenv = deletenode(&(info->env), i);
			i = 0;
			n = info->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (info->changedenv);
}

/**
 * setenviron - init new enviroment
 * @info: param struct
 * @st: string
 * @val: value
 * Return: 0
 */

int setenviron(info_t *info, char *st, char *val)
{
	char *buffer = NULL, *s;
	list_t *n;

	if (!st || !val)
		return (0);
	buffer = malloc(_strlen(st) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, st);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	n = info->env;
	while (n)
	{
		s = startwith(n->str, st);
		if (s && *s == '=')
		{
			free(n->str);
			n->str = buffer;
			info->changedenv = 1;
			return (0);
		}
		n = n->next;
	}
	addendnode(&(info->env), buffer, 0);
	free(buffer);
	info->changedenv = 1;
	return (0);
}
