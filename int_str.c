#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
/**
 * int2str - converts signed int to string
 * @length: the required data type
 * @ptr: the required number
 * @put_positive_sign: the sign of the number
 * Return: on success a string (str)
 */
char *int2str(char length, void const * const ptr, char put_positive_sign)
{
	char *str;
	signed long int n, rem, num, len, i;
	bool isNegative = false;

	if (length == 'l')
		num = *((signed long int *)ptr);
	else if (length == 'h')
		num = *((signed short int *)ptr);
	else if (length == '\0')
		num = *((signed int *)ptr);
	n = num;
	len = i = 0;
	if (num == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (num < 0)
	{
		isNegative = true;
		num = -num;
	}
	while (num != 0)
	{
		rem = num % 10;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / 10;
	}
	if (isNegative)
		str[i++] = '-';
	if (put_positive_sign == '1')
		str[i++] = '+';
	str[i] = '\0';
	reverse(str);
	return (str);
}
