#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @in: the info struct
 * @pa: path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *in, char *pa)
{
	struct stat st;

	(void)in;
	if (!pa || stat(pa, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pastr: the path string
 * @stat: starting index
 * @stp: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pastr, int stat, int stp)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = stat; i < stp; i++)
		if (pastr[i] != ':')
			buf[k++] = pastr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cd in the path string
 * @in: the info struct
 * @pastr: the path string
 * @cd: the cd to find
 *
 * Return: full path of cd if found or NULL
 */
char *find_path(info_t *in, char *pastr, char *cd)
{
	int i = 0;
	int curr_pos = 0;
	char *path;

	if (!pastr)
		return (NULL);
	if ((_strlen(cd) > 2) && starts_with(cd, "./"))
	{
		if (is_cmd(in, cd))
			return (cd);
	}
	while (1)
	{
		if (!pastr[i] || pastr[i] == ':')
		{
			path = dup_chars(pastr, curr_pos, i);
			if (!*path)
				_strcat(path, cd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cd);
			}
			if (is_cmd(in, path))
				return (path);
			if (pastr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
