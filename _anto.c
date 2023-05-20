#include "shell.h"

/**
 * interactive - returns true if shell is interractive mode
 *
 * @in: struct address
 *
 * Return: 1 if interactive mode, 0 if otherwise (error)
 */
int interactive(info_t *in)
{
	return (isatty(STDIN_FILENO) && in->readfd <= 2);
}

/**
 * is_delim - checks if characters is a delimeter
 *
 * @a: the char to checks
 *
 * @deli: the delimeter sting
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char a, char *deli)
{
	while (*deli)
		if (*deli++ == a)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 *
 * @a: the character to input
 *
 * Return: 1 if a is alphabetic, 0 otherwise
 */
int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - coverts a string to an integer
 *
 * @b: the sting to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *b)
{
	int k, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (k = 0; b[k] != '\0' && flag != 2; k++)
	{
		if (b[k] == '-')
			sign *= -1;

		if (b[k] >= '0' && b[k] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (b[k] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
