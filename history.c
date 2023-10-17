#include "shell.h"

/**
 * *gethistoryfile - get history
 * @info: param struct
 * Return: string
 */

char *gethistoryfile(info_t *info)
{
	char *buffer, *d;

	d = getenv(info, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(d) + _strlen(HISTORY) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, d);
	_strcat(buffer, "/");
	_strcat(buffer, HISTORY);
	return (buffer);
}

/**
 * writeinhistory - create file
 * @info: param struct
 * Return: 1 or -1 for fail
 */

int writeinhistory(info_t *info)
{
	char *name = gethistoryfile(info);
	list_t *n = NULL;
	ssize_t fd;

	if (!name)
		return (-1);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (fd == -1)
		return (-1);
	for (n = info->history; n; n = n->next)
	{
		_fdputs(n->str, fd);
		_fdput('\n', fd);
	}
	_fdput(buffer_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readfromhistory - read history
 * @info: param struct
 * Return: history count or 0
 */

int readfromhistory(info_t *info)
{
	struct stat s;
	char *buffer = NULL, *name = gethistoryfile(info);
	ssize_t fd, len, size = 0;
	int i, j = 0, count = 0;

	if (!name)
		return (0);
	fd = open(name, O_RDONLY);
	free(name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &s))
		size = s.st_size;
	if (size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (size + 1));
	if (!buffer)
		return (0);
	len = read(fd, buffer, size);
	buffer[size] = 0;
	if (len < 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			buildhistory(info, buffer + j, count++);
			j = i + 1;
		}
	if (j != i)
		buildhistory(info, buffer + j, count++);
	free(buffer);
	info->historycount = count;
	while (info->historycount-- > MAXHISTORY)
	{
		deletenode(&(info->history), 0);
	}
	renumhistory(info);
	return (info->historycount);
}

/**
 * buildhistory - add entry to history
 * @info: param struct
 * @buffer: buffer
 * @count: counter
 * Return: 0
 */

int buildhistory(info_t *info, char *buffer, int count)
{
	list_t *n = NULL;

	if (info->history)
		n = info->history;
	addendnode(&n, buffer, count);
	if (!info->history)
		info->history = n;
	return (0);
}

/**
 * renumhistory - renumber histroy
 * @info: param struct
 * Return: history count
 */

int renumhistory(info_t *info)
{
	list_t *n = info->history;
	int i = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (info->historycount = i);
}
