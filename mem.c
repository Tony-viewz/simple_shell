#include "shell.h"

/**
 * bfree - free a poiter and NULLS the address
 * @pt: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0
 */
int bfree(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
