#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *	with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *equals_pos, c;
	int result;

	equals_pos = _strchr(str, '=');
	if (!equals_pos)
		return (1);
	c = *equals_pos;
	*equals_pos = 0;
	result = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equals_pos = c;
	return (result);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *equals_pos;

	equals_pos = _strchr(str, '=');
	if (!equals_pos)
		return (1);
	if (!*++equals_pos)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *alias_start, *alias_end;

	if (node)
	{
		alias_start = node->str;
		alias_end = _strchr(alias_start, '=');
		for (; alias_start <= alias_end; alias_start++)
			_putchar(*alias_start);
		_putchar('\'');
		_puts(alias_end + 1);
		_puts("'\n");
		return (1);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *	constatant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int index = 0;
	char *equals_pos;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		equals_pos = _strchr(info->argv[index], '=');
		if (equals_pos)
			set_alias(info, info->argv[index]);
		else
			print_alias(node_starts_with(info->alias, info->argv[index], '='));
	}

	return (0);
}
