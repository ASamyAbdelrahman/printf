#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>
/*format_struct.c -> Abdullrahmen*/
struct Format_str
{
	char specifier;
	char length;
	unsigned int precision;
	unsigned int width;
	char *flags;
	void *variable;
};
struct Format_str *str2format(char const *str);
unsigned int handles(struct Format_str *format,
				char const *str, unsigned int i,
				unsigned int j);
char *sub_string(char const *str, unsigned int n);
char *_strncpy(char *dest, char const *src, int n);
int is_in_str(char value, char *str);

/*_putchar.c -> Samy*/
unsigned int str_len(char *str);
char *capitalize(char *str);
char *reverse(char *str);

/*_printf.c -> Abdullrahmen*/
char *ptr2str(void const * const ptr);
int _printf(const char *format, ...);

/*int2str.c -> Samy */
char *int2str(char length, void const * const ptr); /* length {'\0' , 'l', 'h'} */
char *uint2str(const unsigned int n);
int str2int(char *str);

/*format_struct2string.c -> Abdullrahmen*/
char *format2str(struct Format_str *f_str);
char *handle_variable(struct Format_str *f_str);
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
