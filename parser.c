#include "shell.h"

/**
 * iscmd - see if file is executable command
 * @info: param struct
 * @p: path
 * Return: 1 or 0 for fail
 */

int iscmd(info_t *info, char *p)
{
	struct stat s;

	(void)info;
	if (!p || stat(p, &s))
	{
		return (0);
	}
	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * *dupchar - duplicate character
 * @p: path
 * @beg: beginning index
 * @end: endding index
 * Return: pointer
 */

char *dupchar(char *p, int beg, int end)
{
	int i, j;
	static char buffer[1024];

	for (j = 0, i = beg; i < end; i++)
	{
		if (p[i] != ':')
		{
			buffer[j++] = p[i];
		}
	}
	buffer[j] = 0;
	return (buffer);
}

/**
 * *searchpath - search that cmd the path
 * @info: param struct
 * @p: path
 * @cmd: cmd
 * Return: path of cmd or null
 */

char *searchpath(info_t *info, char *p, char *cmd)
{
	char *pp;
	int i = 0, now = 0;

	if (!p)
		return (NULL);
	if ((_strlen(cmd) > 2) && startwith(cmd, "./"))
	{
		if (iscmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!p[i] || p[i] == ':')
		{
			pp = dupchar(p, now, i);
			if (!*pp)
			{
				_strcat(pp, cmd);
			}
			else
			{
				_strcat(pp, "/");
				_strcat(pp, cmd);
			}
			if (iscmd(info, pp))
				return (PP);
			if (!p[i])
				break;
			now = i;
		}
		i++;
	}
	return (NULL);
}
