#include "shell.h"

/**
 * _myhistory - display the historu list, one command by line
 * @info: Struct conta potential argu. used to maint const function prototype.
 * Return: Always 0
 */
int _myhetory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unst_alias - wsts alias to str
 * @info: Paramet stru
 * @str: the str
 *
 * Return: Always 0 on sucess, 1 on error
 */
int unset_alias(info_t, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, "=");
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delet_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: Parameter str
 * @str: the string alias
 *
 * Return: Always 0 on succ, 1 on err
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias str
 * @node: the alias node
 *
 * Return: Always 0 on suc, on err
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * 
