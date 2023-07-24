#include "main.h"

/**
 * convert2signed - converts the data type of a number
 * @num: the required number
 * @length: the required data type
 * Return: casted value of num
 */

long int convert2signed(long int num, char length)
{
	if (length == 'l')
		return (num);
	else if (length == 'h')
		return ((short)num);

	return ((int)num);
}

/**
 * convert2unsigned - converts the data type of a number
 * @num: the required number
 * @length: the required data type
 * Return: casted value of num
 */
unsigned long int convert2unsigned(unsigned long int num, char length)
{
	if (length == 'l')
		return (num);
	else if (length == 'h')
		return ((unsigned short)num);

	return ((unsigned int)num);
}
