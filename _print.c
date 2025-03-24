#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/**
 * _printf - Custom implementation of printf function.
 * @format: Format string containing the characters and specifiers.
 *
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	va_list a;
	int i, counter;
	char c;

	counter = 0;
	va_start(a, format);
	for (i = 0; format[i]; i++)
	{
		if (format[i] == '%' && format[i + 1] != '\0' &&
		    format[i + 1] != 'c' && format[i + 1] != '%')
			continue;

		if (format[i] == '%' && format[i + 1] == 'c')
		{
			c = va_arg(a, int);
			write(1, &c, 1);
			counter++;
			i++;
		}
		else if (format[i] == '%' && format[i + 1] == '%')
		{
			write(1, &format[i], 1);
			counter++;
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			counter++;
		}
	}
	va_end(a);
	return (counter);
}
