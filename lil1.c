#include "shell.h"

/**
 * list_len - determines length of linked list
 * @w: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *w)
{
	size_t k = 0;

	while (w)
	{
		w = w->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @had: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *had)
{
	list_t *node = had;
	size_t k = list_len(had), i;
	char **sts;
	char *str;

	if (!had || !k)
		return (NULL);
	sts = malloc(sizeof(char *) * (k + 1));
	if (!sts)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (i = 0; i < k; i++)
				free(sts[i]);
			free(sts);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		sts[k] = str;
	}
	sts[k] = NULL;
	return (sts);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @w: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *w)
{
	size_t k = 0;

	while (w)
	{
		_puts(convert_number(w->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(w->str ? w->str : "(nil)");
		_puts("\n");
		w = w->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @d: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char d)
{
	char *f = NULL;

	while (node)
	{
		f = starts_with(node->str, prefix);
		if (f && ((d == -1) || (*f == d)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of node
 * @had: pointer to list had
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *had, list_t *node)
{
	size_t k = 0;

	while (had)
	{
		if (had == node)
			return (k);
		had = had->next;
		k++;
	}
	return (-1);
}
