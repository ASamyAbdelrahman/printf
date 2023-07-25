#include <string.h>
#include <stdio.h> /* till print_string function completed */
#include <unistd.h>
#include "main.h"

#define MAX_BUFFER_SIZE 10

/*
* ptr2str - Convert a void pointer to string
* @ptr : The pointer
* Return : The string (in heap) (converted from the pointer)
*/
char *ptr2str(void const * const ptr)
{
	char *hex;

	hex = malloc(20);
	sprintf(hex, "%lx",(unsigned long) ptr);
	return (hex);
	/*return (int2hex('l', ptr));*/
}

/*
* get_type - get the type of the variable passing to _printf
* @str : the string begin with %
* Return : The following:
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
}

/**
* debug_print_Format - print all the members of Format_str struct
* @f_str: Format_str struct pointer
*/
void debug_print_Format(struct Format_str *format)
{
	printf("\nspecifier : '%c'", format->specifier);
	printf("\nlength : '%c'", format->length);
	printf("\nprecision : '%u'", format->precision);
	printf("\nwidth : '%u'", format->width);
	printf("\nflags : '%s'\n", format->flags); 
}

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

void *get_variable(va_list *args, struct Format_str *f_str)
{
	void *var;

	switch(get_type(f_str))
	{
	case 0:
		return (0);
	case 7:
	case 8:
		return (va_arg(*args, void*));
		break;
	case 1:
		var = malloc(sizeof(int));
		*((int*)var) = va_arg(*args, int);
		return (var);
	case 2:
		var = malloc(sizeof(short));
		*((short*)var) = va_arg(*args, int);
		return (var);
	case 3:
		var = malloc(sizeof(long));
		*((long*)var) = va_arg(*args, long);
		return (var);
	case 4:
		var = malloc(sizeof(unsigned int));
		*((unsigned int*)var) = va_arg(*args, unsigned int);
		return (var);
	case 5:
		var = malloc(sizeof(unsigned short));
		*((unsigned short*)var) = va_arg(*args, unsigned int);
		return (var);
	case 6:
		var = malloc(sizeof(unsigned long));
		*((unsigned long*)var) = va_arg(*args, unsigned long);
		return (var);
	case 9:
		var = malloc(sizeof(char));
		*((char*)var) = va_arg(*args, int);
		return (var);
	}
	return (0);
}

void free_Format(struct Format_str *format)
{
	free(format);
	free(format->flags);
	switch(get_type(format))
	{
	case 0:
	case 7:
	case 8:
		break;
/*	default:
		free(format->variable);*/
	}
	free(format->str);
}

/**
* handle_buffer - Add a string to the buffer and when the buffer is full write
* it to standard output and fill it again with remaining string and repeat this 
* process till the string is ended.
* @buffer : The buffer
* @str : String to add to the buffer
* @n_char_printed : will increased by the number of characters printed
* Return: The new buffer
*/
char *handle_buffer(char *buffer, char const *str, unsigned int str_len_, int *n_char_printed)
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
			write (1, buffer, len);
			n_char_printed += len;
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
* @foramt : Is a character string. The format string is composed of zero or more directives
* Return : The number of characters printed (excluding the null byte)
*/
int _printf(const char *format, ...)
{
	int n_chars_printed = 0;
	va_list args;
	int i = 0;
	char *buffer, *str;
	struct Format_str *f_str;

	if(!format)
		write(1, "NULL", 4);

	va_start(args, format);
	buffer = malloc(MAX_BUFFER_SIZE);
	if (!buffer)
		return (-1);
	buffer[0] = '\0';
	while(format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
			{
				buffer = handle_buffer(buffer, "%", 1, &n_chars_printed);
				i += 2;
				continue;
			}
			f_str = str2format(&format[i]);

			/*debug_print_Format(f_str);
			printf("type : %i\n", get_type(f_str));*/

			f_str->variable = get_variable(&args, f_str);
			if (!f_str->variable)
			{
				buffer = handle_buffer(buffer, "%", 1, &n_chars_printed);
				++i;
				continue;
			}
			f_str->str = get_final_str(f_str);
			buffer = handle_buffer(buffer, f_str->str, str_len(f_str->str), &n_chars_printed);
			i += get_format_len(f_str) + 1;
			free_Format(f_str);
		}
		else
		{
			buffer = handle_buffer(buffer, &format[i], 1, &n_chars_printed);
			++i;
		}
	}
	write(1, buffer, strlen(buffer));
	n_chars_printed += strlen(buffer);
	free(buffer);
	va_end(args);
	return (n_chars_printed);
}


/**
* main - test main
* Return: always 0
*/
int main(void)
{
	int i = 555;
	char str[] = "Hello";

/*	_printf("123456789123456789\n");
	printf("123456789123456789\n");*/

	_printf("->'%R'<-\n", str);


	_printf("'%28s'\n", str);
	printf("'%28s'\n", str);

	_printf("'%#- 2.10s'\n", str);
	printf("'%#- 2.10s'\n", str);

	_printf("'%-#15.9lx'\n", i);
	printf("'%-#15.9lx'\n", i);

	_printf("'% #5.10hx'\n", i);
	printf("'% #5.10hx'\n", i);

	_printf("'%+- #015.5X'\n", i);
	printf("'%+- #015.5X'\n", i);

	_printf("'%#X'\n", i);
	printf("'%#X'\n", i);  

	_printf("'%#X'\n", 0);
	printf("'%#X'\n", 0);

	_printf("'%b'\n", i);
	printf("'%b'\n", i);
	/*_printf("Hello there >%+-+  23.55lX<", i);*/
	/*_printf("% kd125");*/
	return (0);
}

