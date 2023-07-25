#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include "string.h"

char *get_final_str(struct Format_str *format)
{
	char *str = 0;
	unsigned int len = 0;
	char is_zero = 0;

	if (!format)
		return (0);
	format->str = handle_variable(format);
	if (*format->str == '0')
		is_zero = 1;
	format->str = handle_precision(format);
	
	if (is_in_str('#', format->flags) && (format->specifier == 'x' || /* # flag */
						format->specifier == 'X' ||
						format->specifier == 'o') && !is_zero)
	{
		len = strlen(format->str);
		if (format->specifier == 'o')
			str = malloc(len + 2);
		else
			str = malloc(len + 3);
		if (!str)
			return (0);
		str[0] = '0';
		if (format->specifier == 'X')
			str[1] = 'X';
		else
			str[1] = 'x';
		if (format->specifier == 'o')
		{
			str[len + 1] = '\0';
			_strncpy(&str[1], format->str, len);
		}
		else
		{
			str[len + 2] = '\0';
			_strncpy(&str[2], format->str, len);
		}
		free(format->str);
		format->str = str;
	}
	format->str = handle_width(format);
	return (format->str);
}

char *handle_variable(struct Format_str *format)
{
	char *str = 0;
	unsigned int len;

	switch (format->specifier)
	{
	case 'd':
	case 'i':
		if (is_in_str('+', format->flags))
			format->str = int2str(format->length, format->variable, 1);
		else
			format->str = int2str(format->length, format->variable, 0);
		break;
	case 'u':
		if (is_in_str('+', format->flags))
			format->str = uint2str(format->length, format->variable, 1);
		else
			format->str = uint2str(format->length, format->variable, 0);
		break;
	case 'o':
		format->str = int2octal(format->length, format->variable);
		if (is_in_str('#', format->flags))
		{
			len = strlen(format->str);
			str = malloc(len + 2);
			if (!str)
				return (0);
			str[0] = '0';
			str[len + 1] = '\0';
			_strncpy(&str[1], format->str, len);
			free(format->str);
			format->str = str;
		}
		break;

	case 'x':
		format->str = int2hex(format->length, format->variable);
		break;
	case 'X':
		format->str = int2hex(format->length, format->variable);
		str = capitalize(format->variable);
		break;
	case 'b':
		str = uint2bin(*((unsigned int*)format->variable));
		break;
	/*case 'S':
		str = custom_specifier_S(format->variable);
		break;*/
	case 'r':
		str = reverse(format->variable);
		break;
	case 's':
		format->str = sub_string(format->variable, strlen(format->variable));
		break;
	case 'p':
		format->str = ptr2str(format->variable);
		break;
	case 'R':
		str = rot13(format->variable);
		break;
	}
	return (format->str);
}

char *handle_precision(struct Format_str *format)
{
	char *str = 0;
	unsigned int i = 0, len = 0;

	if (!format->precision || !format->is_number)
		return (format->str);
	len = strlen(format->str);
	if (format->precision <= len)
		return (format->str);

	str = malloc(format->precision + 1);
	if (!str)
		return (0);
	for (i = 0; i < format->precision - len; ++i)
		str[i] = '0';
	_strncpy(&str[i], format->str, len);
	str[format->precision] = '\0';
	free(format->str);
	format->str = str;

	return (format->str);
}

char *handle_width(struct Format_str *format)
{
	char *str = 0;
	unsigned int i = 0, len = 0;

	if (!format->width && !format->flags)
		return (format->str);

	len = strlen(format->str);

	if ((is_in_str(' ', format->flags) || is_in_str('+', format->flags)) && 
		format->specifier != 'x' && format->specifier != 'X' && format->specifier != 'o')
	{
		str = malloc(len + 2);
		if (is_in_str(' ', format->flags))
			str[0] = ' ';
		str[len + 1] = '\0';
		_strncpy(&str[1], format->str, len);
		free(format->str);
		format->str = str;
	}	

	len = strlen(format->str);
	if (format->width <= len)
		return (format->str);

	str = malloc(format->width + 1);
	if (!str)
		return (0);
	str[format->width] = '\0';
	if (is_in_str('-', format->flags))
		if(is_in_str('0', format->flags) && format->is_number &&
		format->specifier != 'x' && format->specifier != 'X' && format->specifier != 'o')
			for (i = format->width - 1; i >= len; --i)
				str[i] = '0';
		else
			for (i = format->width - 1; i >= len; --i)
				str[i] = ' ';
	else
		if (is_in_str('0', format->flags) && format->is_number &&
		format->specifier != 'x' && format->specifier != 'X' && format->specifier != 'o')
			for (i = 0; i < format->width - len; ++i)		
				str[i] = '0';
		else
			for (i = 0; i < format->width - len; ++i)
				str[i] = ' ';

	if (is_in_str('-', format->flags))
		_strncpy(str, format->str, len);
	else
		_strncpy(&str[i], format->str, len);
	free(format->str);
	format->str = str;
	return (format->str);	
}

