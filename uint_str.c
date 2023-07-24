#include "main.h"
#include <stdlib.h>

/**
 * uint2str - converts unsigned int to string
 * @num: the required number
 * Return: on success a string (str)
 */
char *uint2str(unsigned int num)
{
	char *str;
	unsigned int n, rem;
	int len, i;

	n = num;
	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (str != NULL)
	{
		for (i = 0; i < len; i++)
		{
			rem = num % 10;
			num = num / 10;
			str[len - (i + 1)] = rem + '0';
		}
	}
	str[len] = '\0';
	return (str);
}
