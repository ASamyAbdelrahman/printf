#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>

/*format_struct.c -> Abdullrahmen*/
struct Format_str
{
	char specifier;
	char length;
	char is_number;
	unsigned int precision;
	unsigned int width;
	unsigned int len;
	char *flags;
	char *str; /*final string*/
	void *variable;
};
struct Format_str *str2format(char const *str);
unsigned int handles(struct Format_str *format,
				char const *str, unsigned int i,
				unsigned int j);
char *sub_string(char const *str, unsigned int n);
char *_strncpy(char *dest, char const *src, int n);
char is_in_str(char value, char *str);

/*_putchar.c -> Samy*/
unsigned int str_len(char *str);
char *capitalize(char *str);
char *reverse(char *str);

/*utilz.c -> Abdullrahmen*/
char get_type(struct Format_str *format);
char get_type2(struct Format_str *format);
void debug_print_Format(struct Format_str *format);
unsigned int get_format_len(struct Format_str *format);
char *ptr2str(void const * const ptr);

/*_printf.c -> Abdullrahmen*/
char *ptr2str(void const * const ptr);
void *get_variable(va_list *args, struct Format_str *format);
void free_Format(struct Format_str *format);
int _printf(const char *format, ...);
char __printf__(const char *format, int *n_printed, int *i, va_list *args,
		char *buffer, struct Format_str *f_str);

/*int2str.c -> Samy */
char *int2str(char length, void const * const ptr, char put_positive_sign); /* length {'\0' , 'l', 'h'} */
char *uint2str(char length, void const * const ptr, char put_positive_sign);
int str2int(char *str);

/*format2final_str.c -> Abdullrahmen*/
char *get_final_str(struct Format_str *format);
char *handle_variable2(struct Format_str *format, char *str, unsigned int len);
char *handle_variable(struct Format_str *format);
char *handle_precision(struct Format_str *format);
char *handle_buffer(char *buffer, char const *str, unsigned int str_len_, int *n_char_printed);

/*handle_width.c -> Abdullrahmen*/
char *handle_width(struct Format_str *format);
char *handle_width2(struct Format_str *format, char *str, unsigned int i, unsigned int len);

/*numerical_conversions.c -> Samy -> all strings are in the heap (don't forget to free)*/
char *uint2bin(unsigned int n);
char *int2octal(char length, void const * const ptr); /* length {'\0' , 'l', 'h'} */
char *int2hex(char length, void const * const ptr); /* length {'\0' , 'l', 'h'} */
char *custom_specifier_S(char *str);
char *rot13(char *str);

#endif /* MAIN_H */
