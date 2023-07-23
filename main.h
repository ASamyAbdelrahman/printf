#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>
/*format_struct.c -> Abdullrahmen*/
struct Format_str
{
	char specifier;
	char length;
	int precision;
	int width;
	char *flags;
	void *variable;
}
struct Format_str *str2format(char const * str);
void free_Format_str(struct Format_str *ptr);

/*_putchar.c -> Samy*/
int _putbuffer(char *str, unsigned int size);
unsigned int str_len(char *str);
char *capitalize(char *str);
char *reverse(char *str);

/*_printf.c -> Abdullrahmen*/
char *ptr2str(void *ptr);
int _printf(const char *format, ...);

/*int2str.c -> Samy */
char *int2str(char length, void const * const ptr); /* length {'\0' , 'l', 'h'} */
char *uint2str(const unsigned int n);
int str2int(char *str);

/*handle_percentage.c -> Abdullrahmen*/
char *handle_percentage(char *str, void const * const ptr);
char *handle_variable(char *str, void const * const ptr);
char *handle_precision(char *str);
char *handle_width(char *str);
char *handle_flag(char *str);

/*numerical_conversions.c -> Samy -> all strings are in the heap (don't forget to free)*/
char *uint2bin(unsigned int n);
char *int2octal(char length, void const * const ptr); /* length {'\0' , 'l', 'h'} */
char *int2hex(char length, void const * const ptr); /* length {'\0' , 'l', 'h'} */
char *custom_specifier_S(char *str);
char *rot13(char *str);

#endif /* MAIN_H */
