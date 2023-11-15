#include "main.h"
/**
 * get_width - calculate the width for printing
 * @format: formated string to print arguments
 * @i: list of arguments to be printed
 * @list: list of arguments
 *
 * Return: width
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else
			break;
	}
	*i = curr_i - 1;
	return (width);
}
