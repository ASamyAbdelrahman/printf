#include "main.h"

/**
 * rot13 - rotates the string by 13 places and integer by 5 places.
 * @str: the required string
 * Return: on success a string (str)
 */
char *rot13(char *str)
{
	unsigned int len, i;

	len = str_len(str);
	str = (char *)malloc(sizeof(char) * (len + 1));
	for (i = 0; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 13;
		else if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] + 13;
		else if (str[i] >= '0' && str[i] <= '9')
			str[i] = str[i] + 5;
	}
	str[i] = '\0';
	return (str);
}
