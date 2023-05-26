#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @m: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *m)
{
	int k = 0;

	if (!m)
		return (0);

	while (*m++)
		k++;
	return (k);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strings
 * @m1: the first string
 * @m2: the second string
 *
 * Return: negative if m1 < m2, positive if m1 > m2, zero if m1 == m2
 */
int _strcmp(char *m1, char *m2)
{
	while (*m1 && m2)
	{
		if (*m1 != *m2)
			return (*m1 - *m2);
		m1++;
		m2++;
	}
	if (*m1 == *m2)
		return (0);
	else
		return (*m1 < *m2 ? -1 : 1);
}

/**
 * starts_with - checks if meedle starts with stack
 * @stack: string to search
 * @good: the substring to find
 *
 * Return: address of next char stack or NULL
 */
char *starts_with(const char *stack, const char *good)
{
	while (*good)
		if (*good++ != *stack++)
			return (NULL);
	return ((char *)stack);
}

/**
 * _strcat - concatenates two strings
 * @st: the destination buffer
 * @sr: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *st, char *sr)
{
	char *set = st;

	while (*st)
		st++;
	while (*sr)
		*st++ = *sr++;
	*st = *sr;
	return (set);
}
