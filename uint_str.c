#include "main.h"

/**
 * uint2str - converts unsigned int to string
 * @num: the required number
 * Return: on success a string (str)
 */
char *uint2str(const unsigned int num)
{
	char *str;
	unsigned int len, i, n, rem;

	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
	return (str);
}
