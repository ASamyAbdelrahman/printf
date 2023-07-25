#include "main.h"
/**
 * int2hex - converts integer to hexa
 * @length: the required data type
 * @ptr: the number
 * Return: string
 */
char *int2hex(char length, void const * const ptr)
{
	char hexa[100];
	int i, j, k;
	unsigned long int n, temp;
	char *str;

	i = 1;
	k = 0;
	if (length == 'l')
		n = *((long int *)ptr);
	else if (length == 'h')
		n = *((short int *)ptr);
	else if (length == '\0')
		n = *((int *)ptr);
	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		hexa[0] = '0';
		str[0] = hexa[0];
		str[1] = '\0';
		return (str);
	}
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 87;
		hexa[i++] = temp;
		n = n / 16;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	for (j = i - 1; j > 0; j--, k++)
	{
		str[k] = hexa[j];
	}
	str[k] = '\0';
	return (str);
}
