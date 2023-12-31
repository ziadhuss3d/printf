#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Size specifier.
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	while (format[curr_i] == 'l' || format[curr_i] == 'h')
	{
		if (format[curr_i] == 'l')
		{
			size += S_LONG;
		}
		else if (format[curr_i] == 'h')
		{
			size += S_SHORT;
		}
		curr_i++;
	}
	*i = curr_i - 1;
	return (size);
}
