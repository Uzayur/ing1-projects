#include "tinyprintf.h"
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>


int pow_number(int a, int b)
{
    int res = 1;
    for (int i = 0; i < b; i++)
        res *= a;
    return res;
}


char *itoa(int n, char *s, const char *base)
{
    int base_type = 0;
    while (base[base_type] != '\0')
	base_type++;

    int index_pow = 0;
    while (pow_number(base_type, index_pow) < n)
	index_pow++;

    index_pow--;
    int index = 0;
    while (index_pow != -1)
    {
	int pow = pow_number(base_type, index_pow);
	if (pow <= n)
	{
	    if (n / pow <= 9)
	    {
		s[index] = '0' + n / pow;
		n = n % pow;
	    }
	    else
	    {
		s[index] = 'a' + n / pow - 10;
		n = n % pow;
	    }
	}
	else
	    s[index] = '0';
	index++;
	index_pow++;
    }
    s[index] = '\0';
    return s;
}

int strlen_s(char *s)
{
	int size = 0;
	while (s[size] != '\0')
		size++;
	return size;
}


int tinyprintf(const char *format, ...)
{
    size_t index = 0;
    size_t size = 0;
    while (format[size] != '\0')
        size++;

    va_list parameters;
    va_start(parameters, format);

    while (format[index] != '\0')
    {
        while (format[index] !='%' && index != size)
        {
	    putchar(format[index]);
	    index++;
	}
        if (format[index + 1] == '%')
	{
	    putchar(37);
	}
	    else if (format[index + 1] == 'c')
	    {
	        putchar(va_arg(parameters, int));
	    }
	    else if (format[index + 1] == 's')
	    {
		char *arg = va_arg(parameters, char *);
		if (!arg)
		{
		    fputs("(null)",stdout);
		    index += 2;
		}
		else
		    fputs(arg,stdout);
	    }
	    index += 2;
    va_end(parameters);
    }
    return index;
}
