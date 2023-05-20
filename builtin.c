#include "shell.h"
#include <stdlib.h>

/**
 * _myexit - exits the shell
 * @in: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: exits with a given exit status
 * (0) if in.argv[0] != 'exit'
 */
int _myexit(info_t *in)
{
	int exitcheck;

	if (in->argv[1])
	{
		exitcheck = _erratoi(in->argv[1]);
		if (exitcheck == -1)
		{
			in->status = 2;
			print_error(in, "Illegal number: ");
			_puts(in->argv[1]);
			_eputchar('\n');
			return (1);
		}
		in->err_num = _erratoi(in->argv[1]);
		return (-2);
	}
	in->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @in: structure containing potential arguments used to maintai
 * constant function prototype
 * Return: always 0
 */
int _mycd(info_t *in)
{
	char *s, *dir, buffer[10240];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		puts("TUDO: >>getcwd failure emsg here<<\n");
	if (!in->argv[1])
	{
		dir = _getenv(in, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(in, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(in->argv[1], "-") == 0)
	{
		if (!_getenv(in, "OLDPWD="))
		{
			puts(s);
			_putchar('\n');
			return (1);
		}
		puts(_getenv(in, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(in, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(in->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(in, "Can't cd to ");
		_puts(in->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(in, "OLDPWD", _getenv(in, "PWD="));
		_setenv(in, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @in: structure containing potential arguments used to maintain
 * constant function prototype
 * Return: always 0
 */
int _myhelp(info_t *in)
{
	char **arg_array;

	arg_array = in->argv;
	puts("help call works: Function not yet implemented \n");
	if (0)
		puts(*arg_array);
	return (0);
}
