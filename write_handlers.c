#include "main.h"

/***WRITE HANDLE***/
/**
 * handle_write_char - Write Handle
 * @c: char
 * @buffer: Buffer
 * @flags: Flags
 * @width: Width
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int a = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pad = '0';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = pad;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/*** WRITE NUMBER ***/
/**
 * write_number - Write Number
 * @is_negative: Lists of arguments
 * @ind: char
 * @buffer: Buffer
 * @flags: Flags
 * @width: Width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int lenght = BUFF_SIZE - ind - 1;
	char pad = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
				lenght, pad, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @pre: Precision specifier
 * @lenght: Number length
 * @pad: Pading char
 * @extra_c: Extra char
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
		int flags, int width, int pre,
		int lenght, char pad, char extra_c)
{
	int a, pad_start = 1;

	if (pre == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (pre == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = pad = ' ';
	if (pre > 0 && pre < lenght)
		pad = ' ';
	while (pre > lenght)
		buffer[--ind] = '0', lenght++;
	if (extra_c != 0)
		lenght++;
	if (width > lenght)
	{
		for (a = 1; a < width - lenght + 1; a++)
			buffer[a] = pad;
		buffer[a] = '\0';
		if (flags & F_MINUS && pad == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
		return (write(1, &buffer[ind], lenght) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], a - 1) + write(1, &buffer[ind], lenght));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			return (write(1, &buffer[pad_start], a - pad_start) +
					write(1, &buffer[ind], lenght - (1 - pad_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], lenght));
}

/***  WRITE UNSIGNED ***/
/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
		char buffer[],
		int flags, int width, int precision, int size)
{
	int lenght = BUFF_SIZE - ind - 1, a = 0;
	char pad = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	{
		return (0);

		if (precision > 0 && precision < lenght)
			pad = ' '; }

	while (precision > lenght)
	{
		buffer[--ind] = '0';
		lenght++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > lenght)
	{
		for (a = 0; a < width - lenght; a++)
			buffer[a] = pad;

		buffer[a] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], lenght) + write(1, &buffer[0], a));
		}
		else
		{
			return (write(1, &buffer[0], a) + write(1, &buffer[ind], lenght));
		}
	}

	return (write(1, &buffer[ind], lenght));
}

/** WRITE POINTER **/
/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index
 * @lenght: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @pad: pad
 * @pad_start: pad start
 * @extra_c: Char representing extra char
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int lenght,
		int width, int flags, char pad, char extra_c, int pad_start)
{
	int a;

	if (width > lenght)
	{
		for (a = 3; a < width - lenght + 3; a++)
			buffer[a] = pad;
		buffer[a] = '\0';
		if (flags & F_MINUS && pad == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], lenght) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], lenght));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[pad_start], a - pad_start) +
					write(1, &buffer[ind], lenght - (1 - pad_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
