#include "main.h"

/**
 * uint2bin - converts unsigned integer to binary
 * @n: the required number
 * Return: on success a string (str)
 */
char *uint2bin(unsigned int n)
{
	unsigned int binary[32];
	int i, j, k;
	char *str;

	i = 0;
	while (n > 0)
	{
		binary[i] = n % 2;
		n = n / 2;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	k = 0;
	for (j = i - 1; j >= 0; j--, k++)
	{
		str[k] = binary[j] + '0';
	}
	str[k] = '\0';
	return (str);
}

