#include "shell.h"

/**
 * get_history_file - gets the history file
 * @in: parameter struct
 *
 * Return: allocated string containing history file
 */

char *get_history_file(info_t *in)
{
	char *bf, *dr;

	dr = _getenv(in, "HOME=");
	if (!dr)
		return (NULL);
	bf = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!bf)
		return (NULL);
	bf[0] = 0;
	_strcpy(bf, dr);
	_strcat(bf, "/");
	_strcat(bf, HIST_FILE);
	return (bf);
}

/**
 * write_history - create a file, or appends to an existing file
 * @in: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *in)
{
	ssize_t df;
	char *file = get_history_file(in);
	list_t *nde = NULL;

	if (!file)
		return (-1);

	df = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (df == -1)
		return (-1);
	for (nde = in->history; nde; nde = nde->next)
	{
		putsfd(nde->str, df);
		putfd('\n', df);
	}
	putfd(BUF_FLUSH, df);
	close(df);
	return (1);
}

/**
 * read_history - reads history from file
 * @in: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *in)
{
	int k, last = 0, linecount = 0;
	ssize_t df, rdlen, fsize = 0;
	struct stat st;
	char *bf = NULL, *file = get_history_file(in);

	if (!file)
		return (0);

	df = open(file, O_RDONLY);
	free(file);
	if (df == -1)
		return (0);
	if (!fstat(df, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bf = malloc(sizeof(char) * (fsize + 1));
	if (!bf)
		return (0);
	rdlen = read(df, bf, fsize);
	bf[fsize] = 0;
	if (rdlen <= 0)
		return (free(bf), 0);
	close(df);
	for (k = 0; k < fsize; k++)
		if (bf[k] == '\n')
		{
			bf[k] = 0;
			build_history_list(in, bf + last, linecount++);
			last = k + 1;
		}
	if (last != k)
		build_history_list(in, bf + last, linecount++);
	free(bf);
	in->histcount = linecount;
	while (in->histcount-- >= HIST_MAX)
		delete_node_at_index(&(in->history), 0);
	renumber_history(in);
	return (in->histcount);
}

/**
 *  build_history_list - adds entry to a history linked list
 *  @in: structure containing potential argument used to maintain
 *  @bf: buffer
 *  @linecount: history linecount, histcount
 *
 *  Return: always 0
 */
int build_history_list(info_t *in, char *bf, int linecount)
{
	list_t *nde = NULL;

	if (in->history)
		nde = in->history;
	add_node_end(&nde, bf, linecount);

	if (!in->history)
		in->history = nde;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @in: structure containing potential arguments used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *in)
{
	list_t *nde = in->history;
	int k = 0;

	while (nde)
	{
		nde->num = k++;
		nde = nde->next;
	}
	return (in->histcount = k);
}
