#include "main.h"

/**
 * is_printable - Evaluates if a char is printable
 * @s: Char to be evaluated
 *
 * Return: 1 or 0
 */

int is_printable(char s)
{
	if (s >= 32 && s < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @a: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: 3
 */

int append_hexa_code(char ascii_code, char buffer[], int a)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[a++] = '\\';
	buffer[a++] = 'x';

	buffer[a++] = map_to[ascii_code / 16];
	buffer[a] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @s: Char to be evaluated
 * Return: 1 or 0
 */

int is_digit(char s)
{
	if (s >= '0' && s <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @number: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */

long int convert_size_number(long int number, int size)
{
	if (size == S_LONG)
		return (number);

	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @number: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */

long int convert_size_unsgnd(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);
	return ((unsigned int)number);
}

