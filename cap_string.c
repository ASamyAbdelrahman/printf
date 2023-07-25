#include "main.h"

/**
 * capitalize - capitalizes all words of a string.
 * @str: the required string.
 * Return: str
 */

char *capitalize(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 32;
		}
	}
	return (str);
}
