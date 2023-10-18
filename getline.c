#include "shell.h"

/**
 * input_buf - buffers chain commands
 * @info: param struct
 * @buffer: string
 * @length: length
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handler);
#if USE_GETLINE
		r = getline(buffer, &len, stdin);
#else
		r = _get_line(info, buffer, &len);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecountflag = 1;
			removecomment(*buffer);
			buildhistory(info, *buffer, info->historycount++);
			{
				 *length = r;
				 info->cmdbuffer = buffer;
			}
		}
	}
	return (r);
}

/**
 * __getinput - get line minus the new line
 * @info: param struct
 * Return: bytes
 */
ssize_t __getinput(info_t *info)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t r = 0;
	char **str = &(info->arg), *p;

	_putchar(buffer_FLUSH);
	r = input_buf(info, &buffer, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buffer + i;

		checkchain(info, buffer, &j, i, length);
		while (j < length)
		{
			if (ischain(info, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->cmdbuffertype = CMD_NORM;
		}

		*str = p;
		return (_strlen(p));
	}
	*str = buffer;
	return (r);
}

/**
 * read_buf - read buffer
 * @info: param struct
 * @buffer : buffer
 * @i: size
 * Return: readd
 */
ssize_t read_buf(info_t *info, char *buffer, size_t *i)
{
	ssize_t readd = 0;

	if (*i)
		return (0);
	readd = read(info->fdread, buffer, READ_BUFFER_SIZE);
	if (readd >= 0)
		*i = readd;
	return (readd);
}

/**
 * _get_line - get the next line of input
 * @info: param struct
 * @str: address
 * @len: size of buffer
 * Return: s
 */
int _get_line(info_t *info, char **str, size_t *len)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, l;
	size_t j;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *str;
	if (p && len)
		s = *len;
	if (i == l)
		i = l = 0;

	r = read_buf(info, buffer, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);
	c = _stringchr(buffer + i, '\n');
	j = c ? 1 + (unsigned int)(c - buffer) : l;
	new_p = __realloc(p, s, s ? s + j : j + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_stringcat(new_p, buffer + i, j - i);
	else
		_stringcpy(new_p, buffer + i, j - i + 1);

	s += j - i;
	i = j;
	p = new_p;

	if (len)
		*len = s;
	*str = p;
	return (s);
}

/**
 * handler - blochs ctrl-c
 * @num: the signal no.
 */
void handler(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(buffer_FLUSH);
}
