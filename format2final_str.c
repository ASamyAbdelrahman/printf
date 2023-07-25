#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include "string.h"

char *get_final_str(struct Format_str *format)
{
	if (!format)
		return (0);
	format->str = handle_variable(format);
	format->str = handle_precision(format);
	format->str = handle_width(format);
	format->str = handle_flags(format);
	return (format->str);
}

char *handle_variable(struct Format_str *format)
{
	switch (format->specifier)
	{
	case 'd':
	case 'i':
		/*format->str = int2str(format->length, f_str->variable);*/
		break;
	case 'u':
		/*format->str = uint2str(format->length, f_str->variable);*/
		break;
	case 'o':
		format->str = int2octal(format->length, format->variable);
		break;
	/*
	case 'x':
		str = int2hex(f_str->length, f_str->variable);
		break;
	case 'X':
		str = int2hex(f_str->length, f_str->variable);
		str = capitalize(f_str->variable);
		break;
	case 'b':
		str = int2bin(*((unsigned int*)f_str->variable));
		break;
	case 'S':
		str = custom_specifier_S(f_str->variable);
		break;
	case 'r':
		str = reverse(f_str->variable);
		break;*/
	case 's':
		format->str = sub_string(format->variable, strlen(format->variable));
		break;
	case 'p':
		format->str = ptr2str(format->variable);
		break;/*
	case 'R':
		str = rot13(f_str->variable);
		break;*/
	}
	return (format->str);
}

char *handle_precision(struct Format_str *format)
{
	char *str = 0;
	unsigned int i = 0, len = 0;

	if (!format->precision)
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

	if (!format->width)
		return (format->str);

	len = strlen(format->str);
	if (format->width <= len)
		return (format->str);

	str = malloc(format->width + 1);
	if (!str)
		return (0);
	for (i = 0; i < format->width - len; ++i)
		str[i] = ' ';
	_strncpy(&str[i], format->str, len);
	str[format->width] = '\0';
	free(format->str);
	format->str = str;
	return (format->str);	
}

char *handle_flags(struct Format_str *format)
{
	if (!format->flags)
		return (format->str);
}


