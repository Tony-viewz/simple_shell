#include "shell.h"

/**
 * **strtow - spilts a string into words, repeat delimiters are ignored
 * @st: the string input
 * @e: the delimeter string
 * Return: a pointer to an array of strings or NULL on failure
 */

char **strtow(char *st, char *e)
{
	int n, m, b, z, num = 0;
	char **t;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!e)
		e = " ";
	for (n = 0; st[n] != '\0'; n++)
		if (!is_delim(st[n], e) && (is_delim(st[n + 1], e) || !st[n + 1]))
			num++;

	if (num == 0)
		return (NULL);
	t = malloc((1 + num) * sizeof(char *));
	if (!t)
		return (NULL);
	for (n = 0, m = 0; m < num; m++)
	{
		while (is_delim(st[n], e))
			n++;
		b = 0;
		while (!is_delim(st[n + b], e) && st[n + b])
			b++;
		t[m] = malloc((b + 1) * sizeof(char));
		if (!t[m])
		{
			for (b = 0; b < m; b++)
				free(t[b]);
			free(t);
			return (NULL);
		}
		for (z = 0; z < b; z++)
			t[m][z] = st[n++];
		t[m][z] = 0;
	}
	t[m] = NULL;
	return (t);
}

/**
 * **strtow2 - splits a string into words
 * @st: the sring input
 * @e: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *st, char e)
{
	int n, m, b, z, num = 0;
	char **t;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (n = 0; st[n] != '\0'; n++)
		if ((st[n] != e && st[n + 1] == e) ||
		    (st[n] != e && !st[n + 1]) || st[n + 1] == e)
			num++;
	if (num == 0)
		return (NULL);
	t = malloc((1 + num) * sizeof(char *));
	if (!t)
		return (NULL);
	for (n = 0, m = 0; m < num; m++)
	{
		while (st[n] == e && st[n] != e)
			n++;
		b = 0;
		while (st[n + b] != e && st[n + b] && st[n + b] != e)
			b++;
		t[m] = malloc((b + 1) * sizeof(char));
		if (!t[m])
		{
			for (b = 0; b < m; b++)
				free(t[b]);
			free(t);
			return (NULL);
		}
		for (z = 0; z < b; z++)
			t[m][z] = st[n++];
		t[m][z] = 0;
	}
	t[m] = NULL;
	return (t);
}
