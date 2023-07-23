#include "main.h"

/**
* is_in_str - Check if the value is in a string
* @value : the value
* @str : the string
* Return: if found 1 else 0
*/
int is_in_str(char value, char *str)
{
	int i = 0;

	while (str[i])
		if (str[i] == value)
			return (1);
	return (0);
}

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to copy
 *
 * Return: pointer to the resulting string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (src[i] != '\0' && i < n)
		dest[i] = src[i++];

	while (i < n)
		dest[i++] = '\0';

	return (dest);
}


/**
* sub_string - Make a substring in the heap
* @str : the source string
* @n : number of bytes to take from the str (without the null char)
* Return: the sub string
*/
char *sub_string(char *str, unsigned int n)
{
	char *sub;
	int i = 0;

	if (!str)
		return (0);
	sub = malloc(n + 1);
	sub = _strncpy(sub, str, n);
	sub[n] = '\0';
	return (sub);
}

/**
* handles - handle width and precision (it is part of str2format function)
* but the betty style force me to not make any function more than 40 lines
* @format: format
* @str: str
* @i: i
* @j: j
* Return: i after the handles
*/
unsigned int handles(struct Format_str *format,
				char const *str, unsigned int i,
				unsigned int j)
{
	char *sub_str;

	j = i;
	while (str[i] >= '0' && str[i] <= '9')
		++i;
	if (i == j)
		format->width = 0;
	else
	{
		sub_str = sub_string(str[j], i - j);
		format->width = str2int(sub_str);
		free(sub_str);
	}

	j = i
	if (str[i++] == '.')
		while (str[i] >= '0' && str[i] <= '9')
			++i;
	else
		--i;
	if (i == j)
		format->precision = 0;
	else
	{
		sub_str = sub_string(str[j], i - j);
		format->precision = str2int(sub_str);
		free(sub_str);
	}
	return (format);
}

/**
* str2format - Convert string to Format struct
* @str : the string
* Return: the Format struct pointer (in heap) or NULL if failed
*/
struct Format_str *str2format(char const *str)
{
	unsigned int i = 0, j = 1;
	struct Format_str *format = 0;
	char specifier[] = "iduoxX";
	char length[] = "lh";
	char flags[] = " #0-+";

	if (str[i++] != '%')
		return (0);

	format = malloc(sizeof(struct Format_str));
/* flags */
	while (is_in_str(str[i], flags))
		++i;
	if (i == j)
		format->flags = 0;
	else
		format->flags = sub_string(str[j], i - j);

/* width and precision */
	i = handles(format, str, i, j);

/* length */
	if (is_in_str(str[i], length))
	{
		format->length = str[i];
		++i;
	}
	else
		format->length = 0;
/* specifier */
	if (is_in_str(str[i], specifier))
		format->specifier = str[i];
	else
		format->specifier = 0;

	return (format);
}

