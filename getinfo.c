#include "shell.h"

/**
 * clearinfo - init struct
 * @info: param struct
 */

void clearinfo(info_t *info)
{
	info->arg = NULL;
	info->argc = 0;
	info->argv = NULL;
	info->path = NULL;
}

/**
 * setinfo - init struct
 * @info: param struct
 * @argvec: argument vector
 */

void setinfo(info_t *info, char **argvec)
{
	int i = 0;

	info->filename = argvec[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		changealias(info);
		changevars(info);
	}
}

/**
 * freeinfo - free struct
 * @info: param struct
 * @fre: free fields
 */

void freeinfo(info_t *info, int fre)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (fre)
	{
		if (!info->cmdbuffer)
			free(info->arg);
		if (info->env)
			freelist(&(info->env));
		if (info->history)
			freelist(&(info->history));
		if (info->alias)
			freelist(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmdbuffer);
		if (info->fdread > 2)
			close(info->fdread);
		_putchar(buffer_FLUSH);
	}
}
