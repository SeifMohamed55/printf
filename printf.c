#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <unistd.h>
/**
 * toString - to string
 * @s: the string
 *
 * Return: str
 */
char *toString(int x)
{
	char *str = malloc(12 * sizeof(char));
	int i = 0;

	if (!str)
	{
		return NULL;
	}
	while (x)
	{
		str[i] = x % 10;
		x = x / 10;
		i++;
	}
	str[i] = '\0';
	str = strrev(str);
	return (str);
}
/**
 * printf - prints a string
 * @format: the format of a string
 *
 * Return: number of bytes
 */
int _printf(const char *format, ...)
{
	va_list list;
	char *str;
	char x;
	int count = 0, y, i = 0, test;
	
	va_start(list, format);
	while (format != NULL && format[i] != '\0')
	{
		x = format[i];
		if (x == '%')
		{
			i++;
			x = format[i];

			switch (x)
			{
				case 'd':
					y = va_arg(list, int);
					str = toString(y);
					test = write(1, str, strlen(str));
					if (test < 0)
						return (-1);
					count += strlen(str);
					break;
				case 'i':
					y = va_arg(list, unsigned int);
					str = toString(y);
					test = write(1, str, strlen(str));
					if (test < 0)
						return (-1);
					count += strlen(str);
					break;
				case 'c':
					y = va_arg(list, int);
					test = write(1, &y, 1);
					if (test < 0)
						return (-1);
					count++;
					break;
				case 's'
					str = va_arg(list, char*);
					test = write(1, str, strlen(str));
					if (test < 0)
						return (-1);
					count += strlen(str);
					break;
				default:
					break;
			}
			i++;
		}
		test = write(1, &x, 1);
		if (test < 0)
			return (-1);
		count++;
		i++;
	}
	return (count);
}
