#include "shell.h"

/**
 * hsh - main
 * @info: param struct
 * @avec: argument vector
 * Return: 0 or 1 for error
 */

int hsh(info_t *info, char **avec)
{
	ssize_t x = 0;
	int builtin = 0;

	while (x != -1 && builtin != -2)
	{
		clearinfo(info);
		if (active(info))
			_puts("$ ");
		_errorputchar(buffer_flush);
		x = getinput(info);
		if (x != -1)
		{
			setinfo(info, avec);
			builtin = searchbuiltin(info);
			if (builtin == -1)
				searchcmd(info);
		}
		else if (active(info))
			_putchar('\n');
		freeinfo(info, 0);
	}
	writeinhistory(info);
	freeinfo(info, 1);
	if (!active(info) && info->status)
		exit(info->status);
	if (builtin == -2)
	{
		if (info->errornum == -1)
			exit(info->status);
		exit(info->errornum);
	}
	return (builtin);
}

/**
 * searchbuiltin - search builtin command
 * @info: param struct
 * Return: -1 if builtin found
 * 0 if builtin excuted or 1 if builtin found but fail
 */

int searchbuiltin(info_t *info)
{
	int builtin = -1, i;
	builtin_group built[] = {
		{"exit", exit},
		{"env", env},
		{"help", help},
		{"history", history},
		{"setenv", setenv},
		{"unsetenv", unsetenv},
		{"cd", cd},
		{"alias", alias},
		{NULL, NULL}
	};

	for (i = 0; built[i].builtintype; i++)
	{
		if (_strcmp(info->argv[0], built[i].builtintype) == 0)
		{
			info->linecount++;
			builtin = built[i].func(info);
			break;
		}
	}
	return (builtin);
}

/**
 * searchcmd - search command path
 * @info: param struct
 * Return: void
 */

void searchcmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecountflag == 1)
	{
		info->linecount++;
		info->linecountflag = 0;
	}
	for (i = 0, j = 0; info->argv[i]; i++)
	{
		if (!isdelim(info->argv[i], "\t\n"))
			j++;
	}
	if (!j)
		return;
	path = searchpath(info, getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkcmd(info);
	}
	else
	{
		if ((active(info) || getenv(info, "PATH=")
					|| info->argv[0][0] == '/') &&
				iscmd(info, info->argv[0]))
			forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printerror(info, "not found\n");
		}
	}
}

/**
 * forkcmd - fork an executable thread to run cmd
 * @info: param struct
 * Return: void
 */

void forkcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getenviron(info)) == -1)
		{
			freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printerror(info, "Permission denied\n");
		}
	}
}
