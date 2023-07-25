#include "main.h"

/**
 * str_len - gets the length of the string.
 * @str: The required string.
 *
 * Return: on success len
 */
unsigned int str_len(char const *str)
{
	unsigned int len;

	len = 0;
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

