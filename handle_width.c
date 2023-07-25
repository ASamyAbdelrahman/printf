#include "main.h"

/**
* handle_width2 - the remaining of handle_width function (betty style)
* @format: format
* @str: str
* @i: i
* @len: len
* Return: format->str after handling the width
*/
char *handle_width2(struct Format_str *format, char *str,
			unsigned int i, unsigned int len)
{
	str = malloc(format->width + 1);
	if (!str)
	{
		free(format->str);
		format->str = 0;
		return (0);
	}
	if (is_in_str('-', format->flags))
		if (is_in_str('0', format->flags) && format->is_number &&
		format->specifier != 'x' && format->specifier != 'X' &&
								format->specifier != 'o')
			for (i = format->width - 1; i >= len; --i)
				str[i] = '0';
		else
			for (i = format->width - 1; i >= len; --i)
				str[i] = ' ';
	else
		if (is_in_str('0', format->flags) && format->is_number &&
		format->specifier != 'x' && format->specifier != 'X' &&
								format->specifier != 'o')
			for (i = 0; i < format->width - len; ++i)
				str[i] = '0';
		else
			for (i = 0; i < format->width - len; ++i)
				str[i] = ' ';
	if (is_in_str('-', format->flags))
		_strncpy(str, format->str, len);
	else
		_strncpy(&str[i], format->str, len);
	str[format->width] = '\0';
	free(format->str);
	format->str = str;
	return (format->str);
}

/**
* handle_width - handles the width
* @format: format struct pointer
* Return: format->str after handling the width
*/
char *handle_width(struct Format_str *format)
{
	char *str = 0;
	unsigned int i = 0, len = 0;

	if (!format->width && !format->flags)
		return (format->str);

	len = str_len(format->str);

	if ((is_in_str(' ', format->flags) || is_in_str('+', format->flags)) &&
			format->is_number && format->specifier != 'x' &&
			format->specifier != 'X' && format->specifier != 'o')
	{
		str = malloc(len + 2);
		if (is_in_str(' ', format->flags))
			str[0] = ' ';
		str[len + 1] = '\0';
		_strncpy(&str[1], format->str, len);
		free(format->str);
		format->str = str;
	}

	if (format->width <= len)
		return (format->str);
	return (handle_width2(format, str, i, len));

}

