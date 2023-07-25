#include "main.h"

/**
 * rot13 - rotates the string by 13 places and integer by 5 places.
 * @str: the required string
 * Return: on success a string (str)
 */
char *rot13(char *str)
{
	char *ptr;
	unsigned int len, i;

	len = str_len(str);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	for (i = 0; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			ptr[i] = str[i] + 13;
		else if (str[i] >= 'a' && str[i] <= 'z')
			ptr[i] = str[i] + 13;
	}
	ptr[i] = '\0';
	return (ptr);
}

