#include "shell.h"

/**
 * _strcpy - copies a string
 * @st: the destination
 * @sr: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *st, char *sr)
{
	int k = 0;

	if (st == sr || sr == 0)
		return (st);
	while (sr[k])
	{
		st[k] = sr[k];
		k++;
	}
	st[k] = 0;
	return (st);
}

/**
 * _strdup - duplicates a string
 * @std: the stirng to duplicate
 *
 * Return: pointer to the duplicate string
 */
char *_strdup(const char *std)
{
	int size = 0;
	char *set;

	if (std == NULL)
		return (NULL);
	while (*std++)
		size++;
	set = malloc(sizeof(char) * (size + 1));
	if (!set)
		return (NULL);
	for (size++; size--;)
		set[size] = *--std;
	return (set);
}

/**
 * _puts - prints an input string
 * @stp: the string to be printed
 *
 * Return: void
 */
void _puts(char *stp)
{
	int k = 0;

	if (!stp)
		return;
	while (stp[k] != '\0')
	{
		_putchar(stp[k]);
		k++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @a: the character to print
 *
 * Return: on success 1
 * on error, -1 is return  and error is set appropriate
 */
int _putchar(char a)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(1, buf, k);
		k = 0;
	}
	if (a != BUF_FLUSH)
		buf[k++] = a;
	return (1);
}
