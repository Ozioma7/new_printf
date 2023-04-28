#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @a: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *a)
{
	int b, curr_a;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_a = *a + 1; format[curr_a] != '\0'; curr_a++)
	{
		for (b = 0; FLAGS_CH[b] != '\0'; b++)
			if (format[curr_a] == FLAGS_CH[b])
			{
				flags |= FLAGS_ARR[b];
				break;
			}
		if (FLAGS_CH[b] == 0)
			break;
	}
	*a = curr_a - 1;
	return (flags);
}

