#include <unistd.h>

/**
 * _putbuffer - writes the string to stdout
 * @str: The string required to print
 * @size: The size of the string
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putbuffer(char *str, unsigned int size)
{
	return (write(1, str, size));
}
