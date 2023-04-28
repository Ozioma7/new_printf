#include "main.h"

void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - Produces output according to a format
 * @format: Is a character string
 * Return: The number of characters printed
 */

int _printf(const char *format, ...)
{
	int a, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list lists;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(lists, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[buff_ind++] = format[a];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			printed_chars++;
		}
		else
		{
				print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &a);
			width = get_width(format, &a, lists);
			precision = get_precision(format, &a, lists);
			size = get_size(format, &a);
			++a;
			printed = handle_print(format, &a, lists, buffer,

					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
			}
	}
	print_buffer(buffer, &buff_ind);

	va_end(lists);
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Buffer
 * @buff_ind: Index at which to add next char, represents the length
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
