#include "main.h"

/**
 * str2int - converts a string to an integer
 * @str: the required string
 * Return: on success the integer value.
 */
int str2int(char *str)
{
	int num;
	unsigned int len, i;

	len = str_len(str);
	num = 0;
	for (i = 0; i < len; i++)
	{
		if (str[len - (i + 1)] >= '0' && str[len - (i + 1)] <= '9')
		num = num + ((str[len - (i + 1)] - '0') * (10 ^ i));
	}
	return (num);
}
