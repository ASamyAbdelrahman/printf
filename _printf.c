#include <unistd.h>
#include "main.h"
#define MAX_BUFFER_SIZE 1024

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
* __printf__ - Write variable to stdout, the standard output stream
* @format : Is a character string.
* The format string is composed of zero or more directives
* @n_printed: number of characters printed
* @i: iterator
* @args: args
* @buffer: buffer
* @f_str: format struct pointer
* Return: if need continue 0 else 1
*/
char __printf__(const char *format, int *n_printed, int *i, va_list *args,
		char *buffer, struct Format_str *f_str)
{
	if (format[*i + 1] == '%')
	{
		buffer = handle_buffer(buffer, "%", 1, n_printed);
		(*i) += 2;
		return (0);
	}
	f_str = str2format(&format[*i]);
	f_str->variable = get_variable(args, f_str);
	if (!f_str->variable)
	{
		if (f_str->specifier == 's' && f_str->precision <= 6)
		{
			handle_buffer(buffer, "(null)", 6, n_printed);
			(*i) += 2;
			return (1);
		}
		if (str_len(format) == 2 && format[*i + 1] == ' ')
			return (2);

		buffer = handle_buffer(buffer, "%", 1, n_printed);
		++(*i);
		return (0);
	}
	if (f_str->specifier == 'c')
		if (*(char *)f_str->variable == '\0')
			++(*n_printed);
	f_str->str = get_final_str(f_str);
	buffer = handle_buffer(buffer, f_str->str, str_len(f_str->str), n_printed);
	(*i) += get_format_len(f_str) + 1;
	free_Format(f_str);
	return (1);
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
	char *buffer = 0, j = 0;
	struct Format_str *f_str = 0;

	if (!format)
		return (-1);
	va_start(args, format);
	buffer = malloc(MAX_BUFFER_SIZE);
	if (!buffer)
		return (-1);
	buffer[0] = '\0';
	while (format[i])
		if (format[i] == '%')
		{
			if (format[i + 1] == ' ' && str_len(format) == 2)
				return (-1);
			else if (str_len(format) == 1)
				return (-1);
			j = __printf__(format, &n_printed, &i, &args, buffer, f_str);
			if (!j)
				continue;
			else if (j == 2)
				return (-1);
		}
		else
			buffer = handle_buffer(buffer, &format[i++], 1, &n_printed);
	write(1, buffer, str_len(buffer));
	n_printed += str_len(buffer);
	free(buffer);
	va_end(args);
	return (n_printed);
}

