#include <limits.h>
#include <stdio.h>/* till print_string function completed */
#include "main.h"

void test1(void)
{

    int len;
    int len2;
    void *addr;
    unsigned int ui;
    len = _printf("Let's try to printf a simple sentence.\n");
    len2 = printf("Let's try to printf a simple sentence.\n");
    ui = (unsigned int)INT_MAX + 1024;
    addr = (void *)0x7ffe637541f0;
    _printf("Length:[%d, %i]\n", len, len);
    printf("Length:[%d, %i]\n", len2, len2);
    _printf("Negative:[%d]\n", -762534);
    printf("Negative:[%d]\n", -762534);
    _printf("Unsigned:[%u]\n", ui);
    printf("Unsigned:[%u]\n", ui);
    _printf("Unsigned octal:[%o]\n", ui);
    printf("Unsigned octal:[%o]\n", ui);
    _printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    _printf("Character:[%c]\n", 'H');
    printf("Character:[%c]\n", 'H');
    _printf("String:[%s]\n", "I am a string !");
    printf("String:[%s]\n", "I am a string !");
    _printf("Address:[%p]\n", addr);
    printf("Address:[%p]\n", addr);
    len = _printf("Percent:[%%]\n");
    len2 = printf("Percent:[%%]\n");
    _printf("Len:[%d]\n", len);
    printf("Len:[%d]\n", len2);
    _printf("Unknown:[%r]\n");
    printf("Unknown:[%r]\n");
	
    _printf("===========================test1=============================\n");
}

void test2(void)
{
	int i = 555;
	char str[] = "Hello";


	_printf("123456789123456789\n");
	printf("123456789123456789\n");

	_printf("'%R'\n", str);

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
}

/**
* main - test main
* Return: always 0
*/
int main(void)
{
	test1();
	test2();
	return (0);
}

