#include <unistd.h>
#include "main.h"

#define MAX_BUFFER_SIZE 10

/**
* ptr2str - Convert a void pointer to string
* @ptr : The pointer
* Return: The string (in heap) (converted from the pointer)
*/
char *ptr2str(void const * const ptr)
{
	return (int2hex('l', &ptr));
}

/**
* get_variable - get the variable from the args according to format type
* @args: the args
* @format: the format
* Return: a pointer to the variable
*/
void *get_variable(va_list *args, struct Format_str *format)
{
	void *var;

	switch (get_type(format))
	{
	case 0:
		return (0);
	case 7:
	case 8:
		return (va_arg(*args, void*));
	case 1:
		var = malloc(sizeof(int));
		*((int *)var) = va_arg(*args, int);
		return (var);
	case 2:
		var = malloc(sizeof(short));
		*((short *)var) = va_arg(*args, int);
		return (var);
	case 3:
		var = malloc(sizeof(long));
		*((long *)var) = va_arg(*args, long);
		return (var);
	case 4:
		var = malloc(sizeof(unsigned int));
		*((unsigned int *)var) = va_arg(*args, unsigned int);
		return (var);
	case 5:
		var = malloc(sizeof(unsigned short));
		*((unsigned short *)var) = va_arg(*args, unsigned int);
		return (var);
	case 6:
		var = malloc(sizeof(unsigned long));
		*((unsigned long *)var) = va_arg(*args, unsigned long);
		return (var);
	case 9: /*character*/
		var = malloc(sizeof(char) + 1);
		*((char *)var) = va_arg(*args, int);
		((char *)var)[1] = '\0';
		return (var);
	}
	return (0);
}

/**
* free_Format - a free function for Format_str structure
* @format: the format
*/
void free_Format(struct Format_str *format)
{
	free(format);
	free(format->flags);
	switch (get_type(format))
	{
	case 0:
	case 7:
	case 8:
		break;
	default:
		free(format->variable);
	}
	free(format->str);
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

/**
* _printf - Write output to stdout, the standard output stream
* @format : Is a character string.
* The format string is composed of zero or more directives
* Return: The number of characters printed (excluding the null byte)
*/
int _printf(const char *format, ...)
{
	int n_printed = 0, i = 0;
	va_list args;
	char *buffer;
	struct Format_str *f_str;

	if (!format)
		write(1, "NULL", 4);
	va_start(args, format);
	buffer = malloc(MAX_BUFFER_SIZE);
	if (!buffer)
		return (-1);
	buffer[0] = '\0';
	while (format[i])
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
			{
				buffer = handle_buffer(buffer, "%", 1, &n_printed);
				i += 2;
				continue;
			}
			f_str = str2format(&format[i]);
			f_str->variable = get_variable(&args, f_str);
			if (!f_str->variable)
			{
				buffer = handle_buffer(buffer, "%", 1, &n_printed);
				++i;
				continue;
			}
			f_str->str = get_final_str(f_str);
			buffer = handle_buffer(buffer, f_str->str, str_len(f_str->str), &n_printed);
			i += get_format_len(f_str) + 1;
			free_Format(f_str);
		}
		else
			buffer = handle_buffer(buffer, &format[i++], 1, &n_printed);
	write(1, buffer, str_len(buffer));
	n_printed += str_len(buffer);
	free(buffer);
	return (n_printed);
}

