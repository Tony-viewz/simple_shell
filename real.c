#include "shell.h"

/**
 * _memset - fills memory with a constant bytes
 * @a: the pointer to the memory area
 * @z: the bytes to fill *a with
 * @c: an amount of bytes to be filled
 * Return: (s) a pointer to the memory area a
 */
char *_memset(char *a, char z, unsigned int c)
{
	unsigned int i;

	for (i = 0; i < c; i++)
		a[i] = z;
	return (a);
}

/**
 * ffree - frees a string of strings
 * @zz: string of strings
 */
void ffree(char **zz)
{
	char **b = zz;

	if (!zz)
		return;
	while (*zz)
		free(*zz++);
	free(b);
}

/**
 * _realloc - reallocates a block of memory
 * @pt: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen
 */
void *_realloc(void *pt, unsigned int old_size, unsigned int new_size)
{
	char *a;

	if (!pt)
		return (malloc(new_size));
	if (!new_size)
		return (free(pt), NULL);
	if (new_size == old_size)
		return (pt);

	a = malloc(new_size);
	if (!a)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		a[old_size] = ((char *)pt)[old_size];
	free(pt);
	return (a);
}
