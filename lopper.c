#include "shell.h"

/**
 * hsh - main shell loop
 * @in: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *in, char **argv)
{
	ssize_t z = 0;
	int builtin_ret = 0;

	while (z != -1 && builtin_ret != -2)
	{
		clear_info(in);
		if (interactive(in))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		z = get_input(in);
		if (z != -1)
		{
			set_info(in, argv);
			builtin_ret = find_builtin(in);
			if (builtin_ret == -1)
				find_cmd(in);
		}
		else if (interactive(in))
			_putchar('\n');
		free_info(in, 0);
	}
	write_history(in);
	free_info(in, 1);
	if (!interactive(in) && in->status)
		exit(in->status);
	if (builtin_ret == -2)
	{
		if (in->err_num == -1)
			exit(in->status);
		exit(in->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @in: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin ececuted successfully
 * 1 if builtin found but not successdul,
 * -1 if builtin signals exit()
 */
int find_builtin(info_t *in)
{
	int i, builtin_ret = -1;
	builtin_table vuiltintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; vuiltintbl[i].type; i++)
		if (_strcmp(in->argv[0], vuiltintbl[i].type) == 0)
		{
			in->line_count++;
			builtin_ret = vuiltintbl[i].func(in);
			break;
		}
	return (builtin_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @in: the parameter & return info stuct
 *
 * Return: void
 */
void find_cmd(info_t *in)
{
	char *pa = NULL;
	int m, n;

	in->path = in->argv[0];
	if (in->linecount_flag == 1)
	{
		in->line_count++;
		in->linecount_flag = 0;
	}
	for (m = 0, n = 0; in->arg[m]; m++)
		if (!is_delim(in->arg[m], " \t\n"))
			n++;
	if (!n)
		return;

	pa = find_path(in, _getenv(in, "PATH="), in->argv[0]);
	if (pa)
	{
		in->path = pa;
		fork_cmd(in);
	}
	else
	{
		if ((interactive(in) || _getenv(in, "PATH=")
			|| in->argv[0][0] == '/') && is_cmd(in, in->argv[0]))
			fork_cmd(in);
		else if (*(in->arg) != '\n')
		{
			in->status = 127;
			print_error(in, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @in: the paarmeter & return info struct
 *
 * Return: nothing
 */
void fork_cmd(info_t *in)
{
	pid_t chl_pid;

	chl_pid = fork();
	if (chl_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (chl_pid == 0)
	{
		if (execve(in->path, in->argv, get_environ(in)) == -1)
		{
			free_info(in, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(in->status));
		if (WIFEXITED(in->status))
		{
			in->status = WEXITSTATUS(in->status);
			if (in->status == 126)
				print_error(in, "Permission denied\n");
		}
	}
}
