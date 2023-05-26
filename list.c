#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: pointer to pointer to head node
 * @str: string to store in the node
 * @num: index of the node used by history
 *
 * Return: pointer to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: pointer to pointer to head node
 * @str: string to store in the node
 * @num: index of the node used by history
 *
 * Return: pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *current_node;

	if (!head)
		return (NULL);

	current_node = *head;

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @head: pointer to head node
 *
 * Return: number of nodes in the list
 */
size_t print_list_str(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * delete_node_at_index - deletes a node at a given index
 * @head: pointer to pointer to head node
 * @index: index of the to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @ptr_head: address of pointer to head node
 *
 * Retrun: void
 */
void free_list(list_t **ptr_head)
{
	list_t *node, *next_node, *head;

	if (!ptr_head || !ptr_head)
		return;
	head = *ptr_head;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ptr_head = NULL;
}
