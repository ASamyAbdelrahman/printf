#include "main.h"


/**
* get_type - get the type of the variable passing to _printf
* @format : the format struct
* Return: The following:
* 1 : int
* 2 : short
* 3 : long
* 4 : unsigned int
* 5 : unsigned short
* 6 : unsigned long
* 7 : void pointer
* 8 : string
* 9 : char
* 0 : unknown
*/
char get_type(struct Format_str *format)
{
	format->is_number = 0;
	switch (format->specifier)
	{
	case 'b':
		format->is_number = 1;
		return (4);
	case 'S':
		return (8);
	case 'r':
		return (8);
	case 'R':
		return (8);
	case 'c':
		return (9);
	case 's':
		return (8);
	case 'p':
		return (7);
	case 'i':
	case 'd':
		format->is_number = 1;
		if (!format->length)
			return (1);
		else if (format->length == 'h')
			return (2);
		else if (format->length == 'l')
			return (3);
		else
			return (0);
	}
	return (get_type2(format));
}

/**
* get_type2 - the remaining of get_type function (betty style code forces)
* @format: the format
* Return: type
*/
char get_type2(struct Format_str *format)
{
	switch (format->specifier)
	{
	case 'u':
	case 'o':
	case 'x':
	case 'X':
		format->is_number = 1;
		if (!format->length)
			return (4);
		else if (format->length == 'h')
			return (5);
		else if (format->length == 'l')
			return (6);
		else
			return (0);
	default:
		return (0);
	}
	return (0);
}

/*
* debug_print_Format - print all the members of Format_str struct
* @f_str: Format_str struct pointer
*//*
* void debug_print_Format(struct Format_str *format)
* {
*
*	printf("\nspecifier : '%c'", format->specifier);
*	printf("\nlength : '%c'", format->length);
*	printf("\nprecision : '%u'", format->precision);
*	printf("\nwidth : '%u'", format->width);
*	printf("\nflags : '%s'\n", format->flags);
* }
*/

/**
* get_format_len - get format length in the original string
* @format: the format
* Return: the length
*/
unsigned int get_format_len(struct Format_str *format)
{
	unsigned int len = 0, i = 0, j = 0;

	if (format->flags)
		len += str_len(format->flags);
	if (format->width)
	{
		j = format->width;
		i = 0;
		while (j)
		{
			++i;
			j /= 10;
		}
		len += i;
	}
	if (format->precision)
	{
		j = format->precision;
		i = 0;
		while (j)
		{
			++i;
			j /= 10;
		}
		len += i + 1;
	}
	if (format->length)
		++len;
	if (format->specifier)
		++len;
	return (len);
}

