#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @in: the parameter struct
 * @buff: the char buffer
 * @z: address of current position in buff
 *
 * Return:1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *in, char *buff, size_t *z)
{
	size_t a = *z;

	if (buff[a] == '|' && buff[a + 1] == '|')
	{
		buff[a] = 0;
		a++;
		in->cmd_buf_type = CMD_OR;
	}
	else if (buff[a] == '&' && buff[a + 1] == '&')
	{
		buff[a] = 0;
		a++;
		in->cmd_buf_type = CMD_AND;
	}
	else if (buff[a] == ';')
	{
		buff[a] = 0;
		in->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*z = a;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @in: the parameter struct
 * @buff: the char buff
 * @z: address of current position in buff
 * @k: starting position in buff
 * @nel: length of buff
 *
 * Return: void
 */
void check_chain(info_t *in, char *buff, size_t *z, size_t k, size_t nel)
{
	size_t a = *z;

	if (in->cmd_buf_type == CMD_AND)
	{
		if (in->status)
		{
			buff[k] = 0;
			a = nel;
		}
	}
	if (in->cmd_buf_type == CMD_OR)
	{
		if (!in->status)
		{
			buff[k] = 0;
			a = nel;
		}
	}

	*z = a;
}

/**
 * replace_alias - replace an aliases in the tokenized string
 * @in: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *in)
{
	int k;
	list_t *done;
	char *z;

	for (k = 0; k < 10; k++)
	{
		done = node_starts_with(in->alias, in->argv[0], '=');
		if (!done)
			return (0);
		free(in->argv[0]);
		z = _strchr(done->str, '=');
		if (!z)
			return (0);
		z = _strdup(z + 1);
		if (!z)
			return (0);
		in->argv[0] = z;
	}
	return (1);
}

/**
 * replace_vars - replace vars in the tokenized string
 * @in: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *in)
{
	int k = 0;
	list_t *done;

	for (k = 0; in->argv[k]; k++)
	{
		if (in->argv[k][0] != '$' || !in->argv[k][1])
			continue;

		if (!_strcmp(in->argv[k], "$?"))
		{
			replace_string(&(in->argv[k]),
				_strdup(convert_number(in->status, 10, 0)));
			continue;
		}
		if (!_strcmp(in->argv[k], "$$"))
		{
			replace_string(&(in->argv[k]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		done = node_starts_with(in->env, &in->argv[k][1], '=');
		if (done)
		{
			replace_string(&(in->argv[k]),
				_strdup(_strchr(done->str, '=') + 1));
			continue;
		}
		replace_string(&in->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @oldr: address of aldr string
 * @newr: newr string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **oldr, char *newr)
{
	free(*oldr);
	*oldr = newr;
	return (1);
}
