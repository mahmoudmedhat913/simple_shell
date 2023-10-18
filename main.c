#include "shell.h"

/**
 * main - entry point
 * @argcount: argument counter
 * @argvec: argument vector
 * Return: 0 or 1 for fail
 */

int main(int argcount, char **argvec)
{
	info_t info[] = { info_init };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));
	if (argcount == 2)
	{
		fd = open(argvec[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errorputs(argvec[0]);
				_errorputs(": 0: Can't open ");
				_errorputs(argvec[1]);
				_errorputchar('\n');
				_errorputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->fdread = fd;
	}
	populateenv(info);
	readfromhistory(info);
	hsh(info, argvec);
	return (EXIT_SUCCESS);
}
