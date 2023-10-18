#include "shell.h"

/**
 * env - print the current env
 * @info: param struct
 * Return: Always 0
 */
int env(info_t *info)
{
	printstringlist(info->env);
	return (0);
}

/**
 * *getenv - get value of env vars
 * @info: param struct
 * @name: name
 *
 * Return: value
 */
char *getenv(info_t *info, const char *name)
{
	list_t *n = info->env;
	char *s;

	while (n)
	{
		s = startwith(n->str, name);
		if (s && *s)
			return (s);
		n = n->next;
	}
	return (NULL);
}

/**
 * setenv - init a new env var or modifiy one
 * @info: param struct
 * Return: 0
 */
int setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_errorputs("Incorrect number of arguments\n");
		return (1);
	}
	if (setenviron(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetenv - delete enviroment
 * @info: param struct
 * Return: 0
 */
int unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_errorputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetenviron(info, info->argv[i]);

	return (0);
}

/**
 * populateenv - populate env
 * @info: param struct
 * Return: 0
 */
int populateenv(info_t *info)
{
	list_t *n = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addendnode(&n, environ[i], 0);
	info->env = n;
	return (0);
}
