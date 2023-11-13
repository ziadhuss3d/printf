#include "main.h"
#include <stdlib.h>
static format_specifier format_specifiers[] = {
	{"i", print_integer},
	{"d", print_integer},
	{"c", print_char},
	{"s", print_string}
};
/**
 * _printf - Produces output according to the fotmat
 * @format: A string containing all the characters
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	int count = 0, i;
	format_t z = {0, -1, -1, -1, -1};
	va_list args;

	/* note: If format is NULL */
	if (!format)
		return (-1);

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			z = get_format(&format);
			if (z.flags == NULL)
				return (-1);
			for (i = 0; format_specifiers[i].specifier; ++i)
				if (z.specifier == *format_specifiers[i].specifier)
				{
					format_specifiers[i].function(args, z, &count);
					format++;
					break;
				}
			free(z.flags);
		}
		else
			_putchar(*format++, &count);
	}
	va_end(args);
	return (count);
}
