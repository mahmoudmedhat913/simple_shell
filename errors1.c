#include "shell.h"

/**
 * erroratoi - convert string to integer
 * @str: string
 * Return: converted no. or 0 or -1 for fail
 */
int erroratoi(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * printerror - print error message
 * @info: param struct
 * @str: string
 * Return: converted no. or 0 or -1 for fail
 */
void printerror(info_t *info, char *str)
{
	_errorputs(info->filename);
	_errorputs(": ");
	printd(info->linecount, STDERR_FILENO);
	_errorputs(": ");
	_errorputs(info->argv[0]);
	_errorputs(": ");
	_errorputs(str);
}

/**
 * printd - print integer
 * @in: input
 * @fd: the filedescriptor
 *
 * Return: nu. of characters
 */
int printd(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _errorputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		count++;
	}
	else
		_abs_ = in;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			count++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * *convertnum - converter func
 * @num: number
 * @b: base
 * @f: argument flags
 * Return: string
 */
char *convertnum(long int num, int b, int f)
{
	static char *arr;
	static char buffer[50];
	char sign = 0, *p;
	unsigned long n = num;

	if (!(f & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';
	do {
		*--p = arr[n % b];
		n /= b;
	} while (n != 0);
	if (sign)
		*--p = sign;
	return (p);
}




/**
 * removecomment - function replace '#' with '\0'
 * @buffer: string
 */
void removecomment(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}
