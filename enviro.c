#include "shell.h"

/**
 * _myenv - prints the current environment
 * @in: structure containing potantial argument used to maintain
 * constant function prototype
 * Return: always 0
 */
int _myenv(info_t *in)
{
	print_list_str(in->env);
	return (0);
}

/**
 * _getenv - get the value of an environ variable
 * @in: structure conatining potantial argument used to maintain
 * @use: env var use as a name
 *
 * Return: the value
 */
char *_getenv(info_t *in, const char *use)
{
	list_t *ndle = in->env;
	char *r;

	while (ndle)
	{
		r = starts_with(ndle->str, use);
		if (r && *r)
			return (r);
		ndle = ndle->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initialzw a new environment variable
 * or modify an existing one
 * @in: structure containing potantial argument used to maintain
 * constant function prototype
 * Return: always 0
 */
int _mysetenv(info_t *in)
{
	if (in->argc != 3)
	{
		_puts("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(in, in->argv[1], in->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove an environment variable
 * @in: structure containing potantial arguments used to maintain
 * constant function prototype
 * Return: alway 0
 */
int _myunsetenv(info_t *in)
{
	int k;

	if (in->argc == 1)
	{
		_puts("Too few arguments.\n");
		return (1);
	}
	for (k = 1; k <= in->argc; k++)
		_unsetenv(in, in->argv[k]);

	return (0);
}

/**
 * populate_env_list - populate env linked list
 * @in: structure containing potential argument used to maintain
 * constant function prototype
 * Return: always 0
 */
int populate_env_list(info_t *in)
{
	list_t *ndle = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		add_node_end(&ndle, environ[k], 0);
	in->env = ndle;
	return (0);
}
