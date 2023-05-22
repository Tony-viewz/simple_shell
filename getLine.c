#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @in: parameter struct
 * @bf: address of buffer
 * @len: adress of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *in, char **bf, size_t *len)
{
	ssize_t q = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*bf);
		*bf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		q = getline(bf, &len_p, stdin);
#else
		q = _getline(in, bf, &len_p);
#endif
		if (q > 0)
		{
			if ((*bf)[q - 1] == '\n')
			{
				(*bf)[q - 1] = '\0';
				q--;
			}
			in->linecount_flag = 1;
			remove_comments(*bf);
			build_history_list(in, *bf, in->histcount++);

			{
				*len = q;
				in->cmd_buf = bf;
			}
		}
	}
	return (q);
}

/**
 * get_input - gets a line minus the newline
 * @in: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *in)
{
	static char *bf;
	static size_t k, a, len;
	ssize_t q = 0;
	char **buf_p = &(in->arg), *r;

	_putchar(BUF_FLUSH);
	q = input_buf(in, &bf, &len);
	if (q == -1)
		return (-1);
	if (len)
	{
		a = k;
		r = bf + k;

		check_chain(in, bf, &a, k, len);
		while (a < len)
		{
			if (is_chain(in, bf, &a))
				break;
			a++;
		}

		k = a + 1;
		if (k >= len)
		{
			k = len = 0;
			in->cmd_buf_type = CMD_NORM;
		}

		*buf_p = r;
		return (_strlen(r));
	}

	*buf_p = bf;
	return (q);
}

/**
 * read_buf - reads a buffer
 * @in: parameter struct
 * @bf: buffer
 * @k: size
 *
 * Return: q
 */
ssize_t read_buf(info_t *in, char *bf, size_t *k)
{
	ssize_t q = 0;

	if (*k)
		return (0);
	q = read(in->readfd, bf, READ_BUF_SIZE);
	if (q >= 0)
		*k = q;
	return (q);
}

/**
 * _getline - gets the next line of input from STDIN
 * @in: parameter struct
 * @pr: address of pointer to buffer, preallocated or NULL
 * @lenth: size of preallocated pr buffer if not NULL
 *
 * Return: z
 */
int _getline(info_t *in, char **pr, size_t *lenth)
{
	static char bf[READ_BUF_SIZE];
	static size_t k, len;
	size_t i;
	ssize_t q = 0, z = 0;
	char *r = NULL, *new_p = NULL, *c;

	r = *pr;
	if (r && lenth)
		z = *lenth;
	if (k == len)
		k = len = 0;

	q = read_buf(in, bf, &len);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	c = _strchr(bf + k, '\n');
	i = c ? 1 + (unsigned int)(c - bf) : len;
	new_p = _realloc(r, z, z ? z + i : i + 1);
	if (!new_p)
		return (r ? free(r), -1 : -1);

	if (z)
		_strncat(new_p, bf + k, i - k);
	else
		_strncpy(new_p, bf + k, i - k + 1);

	z += i - k;
	k = i;
	r = new_p;

	if (lenth)
		*lenth = z;
	*pr = r;
	return (z);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
