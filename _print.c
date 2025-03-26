#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/**
 * print_char - Prints a character.
 * @args: Argument list containing the character to print.
 *
 * Return: Number of characters printed.
 */
int print_char(va_list args)
{
	char c = va_arg(args, int);

	return (write(1, &c, 1));
}
/**
 * print_int - Prints a integer.
 * @args: Argument list containing the integer to print.
 *
 * Return: Number of characters printed.
 */
int print_int(va_list args)
{
	int n = va_arg(args, int);
	int i = 20, counter = 0;
	char s[20];
	char c = '-';

	if (n < 0)
	{
		n *= -1;
		counter += write(1, &c, 1);
	}
	while (n > 0)
	{
		c =  n % 10 + 48;
		s[i] = c;
		i--;
		n /= 10;
	}
	counter += write(1, s + i + 1, 20 - i);
	return (counter);
}

/**
 * print_string - Prints a string.
 * @args: Argument list containing the string to print.
 *
 * Return: Number of characters printed.
 */
int print_string(va_list args)
{
	char *str = va_arg(args, char *);
	int counter = 0;

	if (!str)
		str = "(null)";

	while (*str)
		counter += write(1, str++, 1);

	return (counter);
}

/**
 * _printf - Custom implementation of printf function.
 * @format: Format string containing the characters and specifiers.
 *
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i, counter = 0;

	if (!format)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i]; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				return (-1);
			if (format[i + 1] == 'c')
				counter += print_char(args);
			else if (format[i + 1] == 'i' || format[i + 1] == 'd')
				counter += print_int(args);
			else if (format[i + 1] == 's')
				counter += print_string(args);
			else if (format[i + 1] == '%')
				counter += write(1, "%", 1);
			else
			{
				counter += write(1, "%", 1);
				counter += write(1, &format[i + 1], 1);
			}
			i++;
		}
		else
			counter += write(1, &format[i], 1);
	}

	va_end(args);
	return (counter);
}

