#include <stdio.h> /* till print_string function completed */
#include <unistd.h>
#include "main.h"

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
t get_percentage_str - get the full format options of the percentage
* @str : the string (begin with %)
* Return : new string (in heap) with only the format options of the percentage
* or NULL if failed
char *get_percentage_str(char *str)
{
	int i = 1;

	while (str[i] == ' ')
		++i;

	while (str[i]

}*/
/*
* get_type - get the type of the variable passing to _printf
* @str : the string begin with %
* Return : The following:
* 1 : int
* 2 : short
* 3 : long
* 4 : unsigned int
* 5 : unsigned long
* 6 : unsigned short
* 7 : void pointer
* 8 : string
* 9 : char
* 0 : unknown
*/
char get_type(struct Format_str *f_str)
{
	return (0);
}

void debug_print_Format(struct Format_str *f_str)
{
	printf("\nspecifier : '%c'", f_str->specifier);
	printf("\nlength : '%c'", f_str->length);
	printf("\nprecision : '%u'", f_str->precision);
	printf("\nwidth : '%u'", f_str->width);
	printf("\nflags : '%s'\n", f_str->flags); 
}

/*
* _printf - Write output to stdout, the standard output stream
* @foramt : Is a character string. The format string is composed of zero or more directives
* Return : The number of characters printed (excluding the null byte)
*/
int _printf(const char *format, ...)
{
	int n_chars_printed = 0;
	va_list args;
	int i = 0;
	char buffer[1024];
	struct Format_str *f_str;

	va_start(args, format);

	while(format[i])
	{
		if(format[i] == '%')
		{
			f_str = str2format(&format[i]);
			debug_print_Format(f_str);
			free(f_str);
		}
		
		++n_chars_printed;
		printf("%c", format[i]);
/*		write(1, &format[i], 1);*/
		++i;
	}

	va_end(args);
	return (n_chars_printed);
}

int main(void)
{
	int i = 5;
	_printf("%d\n\n", i);
	_printf("Hello there >%+-+  23.55lX<", i);
	return (0);
}

