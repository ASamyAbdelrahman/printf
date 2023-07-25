#include "main.h"

/**
 * int2octal - converts an integer to octal
 * @length: the required data type
 * @ptr: the required number
 * Return: on success string (str)
 */
char *int2octal(char length, void const * const ptr)
{
	unsigned long int octal[100];
	int i, j, k;
	unsigned long int n;
	char *str;

	i = 0;
	if (length == 'l')
		n = *((unsigned long int *)ptr);
	else if (length == 'h')
		n = *((unsigned short int *)ptr);
	else if (length == '\0')
		n = *((unsigned int *)ptr);
	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		octal[0] = '0';
		str[0] = octal[0];
		str[1] = '\0';
		return (str);
	}
	while (n > 0)
	{
		octal[i] = n % 8;
		n = n / 8;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	k = 0;
	for (j = i - 1; j >= 0; j--, k++)
	{
		str[k] = octal[j] + '0';
	}
	str[k] = '\0';
	return (str);
}
