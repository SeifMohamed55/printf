#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
/**
 * toChar - to charachter
 * @c: the digit
 *
 * Return: the char
 */
char toChar(int d)
{
	return (d + '0');
}
/**
 * strrev - reverse a string
 * @str: the string
 *
 * Return: reversed string
 */
char* strrev(char *str)
{
	unsigned int i, j;
	char tmp;

	for (i = strlen(str) - 1, j = 0;j < strlen(str) / 2; i--, j++)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
	return (str);
}
/**
 * toString - to string
 * @x: the number
 *
 * Return: str
 */
char *toString(int x)
{
	char *str = malloc(14 * sizeof(char));
	int i = 0 , bol = 0;
	if (x < 0)
	{
		bol = 1;
		x *= -1;
	}
	if (!str)
	{
		return NULL;
	}
	while (x)
	{
		str[i] = (x % 10) + '0';
		x = x / 10;
		i++;
	}
	if (bol)
	{
		str[i] = '-';
		bol = 0;
		i++;
	}
	str[i] = '\0';
	strrev(str);
	return (str);
}
/**
 * dec_to_binary - gets the number in binary
 * @x: the decimal
 *
 * Return: the number in binary
 */
char *dec_to_binary(unsigned int x)
{
	char *str = malloc(70 * sizeof(char));
	char ch;
	int i = 0;

	if (str == NULL)
		return (NULL);
	while (x)
	{
		ch = toChar(x % 2);
		x /= 10;
		str[i] = ch;
		i++;
	}
	str[i] = '\0';
	return (strrev(str));

}

/**
 * _printf - prints a string
 * @format: the format of a string
 *
 * Return: number of bytes
 */
int _printf(const char *format, ...)
{
	va_list list;
	char *str;
	char x;
	int y, i = 0, test;
    unsigned int count = 0 , zo;
	
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
					free(str);
					break;
				case 'i':
					zo = va_arg(list, unsigned int);
					str = toString(zo);
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
				case 's':
					str = va_arg(list, char *);
					test = write(1, str, strlen(str));
					if (test < 0)
						return (-1);
					count += strlen(str);
					break;
				case '%':
					x = '%';
					test = write(1, &x, 1);
					if (test < 0)
						return (-1);
					count++;
					break;
				case 'r':
					str = va_arg(list, char *);
					test = write(1, strrev(str), strlen(str));
					if (test < 0)
						return (-1);
					count += strlen(str);
					break;
				case 'b':
					zo = va_arg(list, unsigned int);
					str = dec_to_binary(zo);
					test = write(1, str, strlen(str));
					if (test < 0)
						return (-1);
					count += strlen(str);
					break;

				default:
					x = '%';
					test = write(1, &x, 1);
					if (test < 0)
						return (-1);
					x = format[i];
					test = write(1, &x, 1);
					count += 2;
					if (test < 0)
						return (-1);
			}
		}
		else
        	{
			test = write(1, &x, 1);
			count++;
			if (test < 0)
				return (-1);
		}
			i++;
	}
	va_end(list);
	return ((int)count);
}
