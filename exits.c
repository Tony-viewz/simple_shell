#include "shell.h"

/**
 * _strncpy - Copies a string
 * @dest: Pointer to destination buffer
 * @src: Pointer to source string
 * @n: maximum number of character to copy
 *
 * Return: Pointer to destination buffer
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
				j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings
 * @dest: Pointer to destination buffer
 * @src: Pointer to source string
 * @n: Maximum number of characters to append
 *
 * Return: Pointer to destination buffer
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: Pointer to string to search
 * @c: Charater to locate
 *
 * Return: Pointer to first occurrence of C in S, or NULL if not found
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
