#include "shell.h"

/**
 * eputs - prints an inputs string
 * @text: the string to be printed
 *
 * Return: Nothing
 */
void eputs(char *text)
{
	int index = 0;

	if (!text)
		return;
	while (text[index] != '\0')
	{
		_eputchar(text[index]);
		index++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, end errno is set appropriately,
 */
int _eputchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * putfd - write the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putfd(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * putsfd - prints an input string
 * @text: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int putsfd(char *text, int fd)
{
	int index = 0;

	if (!text)
		return (0);
	while (*text)
	{
		index += putfd(*text++, fd);
	}
	return (index);
}
