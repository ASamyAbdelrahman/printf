#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
/**
 * negative_number - checks if the number negative or not
 * @num: the required number
 * Return: 1 if the number is negative
 */
bool negative_number(int num)
{
	bool isNegative = false;

	if (num < 0)
	{
		isNegative = true;
	}
	return (isNegative);
}
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
	if (num == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}
	for (len = 0; n != 0; len++)
	{
		n /= 10;
	}
	str = (char *)malloc(sizeof(char) * (len + 2));
	isNegative = negative_number(num);
	if (isNegative)
		num = -num;
	for (i = 0; num != 0; i++)
	{
		rem = num % 10;
		str[i] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
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
