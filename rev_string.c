#include "main.h"

/**
 * reverse - Reverses a string
 * @str: The required string.
 * Return: The reversed string.
 */
char *reverse(char *str)
{
	char rev = s[0];
	int counter = 0;
	int i;

	while (str[counter] != '\0')
		counter++;
	for (i = 0; i < counter; i++)
	{
		counter--;
		rev = str[i];
		str[i] = str[counter];
		str[counter] = rev;
	}
	return (str);
}
