#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>

/*_putchar.c -> Samy*/
int _putbuffer(char *str); /*1024 bytes*/
void print_string(char *str);
unsigned int str_len(char *str);
char *capitalize(char *str);
char *reverse(char *str);

/*_printf.c -> Abdullrahmen*/
char *ptr2str(void *ptr);
int _printf(const char *format, ...);

/*int2str.c -> Samy */
char *int2str(char length, void *ptr); /* length {'\0' , 'l', 'h'} */
char *uint2str(const unsigned int n);

/*handle_percentage.c -> Abdullrahmen*/
char *handle_percentage(char *str, void const * const ptr);
char *handle_variable(char *str, void const * const ptr);
char *handle_precision(char *str);
char *handle_width(char *str);
char *handle_flag(char *str);

/*numerical_conversions.c -> Samy*/
char *uint2bin(char length, void const * const ptr); /* length {'ul' (unsigned long), 'u' (unsigned int)} */
char *int2octal(char length, void const * const ptr); /* length {'\0' , 'l', 'h'} */
char *int2hex(char length, void const * const ptr); /* length {'\0' , 'l', 'h'} */
char *custom_specifier_S(char *str);
char *rot13(char *str);

#endif /* MAIN_H */
