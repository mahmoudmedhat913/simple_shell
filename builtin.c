#include "shell.h"

/**
 * exit - exit shell
 * @info: param struct
 * Return: exit
 */
int __exit(info_t *info)
{
	int check;

	if (info->argv[1])
	{
		check = erroratoi(info->argv[1]);
		if (check == -1)
		{
			info->status = 2;
			printerror(info, "Illegal number: ");
			_errorputs(info->argv[1]);
			_errorputchar('\n');
			return (1);
		}
		info->errornum = erroratoi(info->argv[1]);
		return (-2);
	}
	info->errornum = -1;
	return (-2);
}

/**
 * cd - change the current direct to process
 * @info: param struct
 * Return: 0
 */
int __cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ret = chdir(info->argv[1]);
	if (ret == -1)
	{
		printerror(info, "can't cd to ");
		_errorputs(info->argv[1]), _errorputchar('\n');
	}
	else
	{
		setenviron(info, "OLDPWD", _getenv(info, "PWD="));
		setenviron(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help - changes the current directory
 * @info: param struct
 * Return: 0
 */
int __help(info_t *info)
{
	char **str;

	str = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*str);
	return (0);
}
