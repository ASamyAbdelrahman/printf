#include "main.h"
#include <unistd.h>
#define MAX_BUFFER_SIZE 1024

/**
* get_final_str - get final string to be printed
* @format: format struct pointer
* Return: the string after adding flags etc..
*/
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
		format->specifier == 'X' || format->specifier == 'o') && !is_zero)
	{
		len = str_len(format->str);
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

/**
* handle_variable2 - the remaining of handle_variable (betty style)
* @format: format
* @len: len
* @str: str
* Return: The string after handle the variable
*/
char *handle_variable2(struct Format_str *format, char *str, unsigned int len)
{
	switch (format->specifier)
	{
	case 'X':
		format->str = int2hex(format->length, format->variable);
		format->str = capitalize(format->str);
		break;
	case 'b':
		format->str = uint2bin(*((unsigned int *)format->variable));
		break;
	/*case 'S':
		format->str = custom_specifier_S(format->variable);
		break;*/
	case 'r':
		format->str = reverse(format->variable);
		break;
	case 's':
		format->str = sub_string(format->variable, str_len(format->variable));
		break;
	case 'p':
		format->str = ptr2str(format->variable);
		len = str_len(format->str);
		str = malloc(len + 3);
		str[0] = '0';
		str[1] = 'x';
		str[len] = '\0';
		_strncpy(&str[2], format->str, len);
		free(format->str);
		format->str = str;
		break;
	case 'R':
		format->str = rot13(format->variable);
		break;
	case 'c':
		format->str = sub_string(format->variable, str_len(format->variable));
	}
	return (format->str);
}

/**
* handle_variable - handles the variable (convert it to string)
* @format: format struct pointer
* Return: the variable after converted to string
*/
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
			len = str_len(format->str);
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
	}
	return (handle_variable2(format, str, len));
}

/**
* handle_precision - handles the precision
* @format: format struct pointer
* Return: format->str after handles the precision
*/
char *handle_precision(struct Format_str *format)
{
	char *str = 0;
	unsigned int i = 0, len = 0;

	if (!format->precision || !format->is_number)
		return (format->str);
	len = str_len(format->str);
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

/**
* handle_buffer - Add a string to the buffer and when the buffer is full write
* it to standard output and fill it again with remaining string
* and repeat this process ntill the string is ended.
* @buffer : The buffer
* @str : String to add to the buffer
* @str_len_ : the length of str
* @n_char_printed : will increased by the number of characters printed
* Return: The new buffer
*/
char *handle_buffer(char *buffer, char const *str, unsigned int str_len_,
						int *n_char_printed)
{
	unsigned int len = 0, i = 0;

	len = str_len(buffer);
	while (i < str_len_)
	{
		while (i < str_len_ && len < MAX_BUFFER_SIZE)
		{
			buffer[len] = str[i];
			++i;
			++len;
		}
		if (len == MAX_BUFFER_SIZE)
		{
			write(1, buffer, len);
			*n_char_printed += len;
			buffer[0] = '\0';
			len = 0;
		}
		else
		{
			buffer[len] = '\0';
		}
	}
	return (buffer);
}

