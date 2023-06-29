#include <stddef.h>
#include <stdlib.h>
#include <time.h>

static int check_parser(char c)
{
    char *s = ";:,-_";

    int index = 0;
    while (s[index] != '\0')
    {
        if (s[index] == c)
            return 1;
        index++;
    }
    return 0;
}

static int valid_string(const char *format)
{
    int year = 0;
    int month = 0;
    int day = 0;
    int other = 0;

    int index = 0;
    while (format[index] != '\0')
    {
        if (format[index] == 'Y')
            year++;
        else if (format[index] == 'M')
            month++;
        else if (format[index] == 'D')
            day++;
        else
            other++;
        index++;
    }

    if (!(year == 1 && month == 1 && day == 1 && other == 2))
        return -1;

    if (check_parser(format[3]) && check_parser(format[1]))
        return 0;

    return -1;
}

static char *my_itoa(int value, char *s)
{
    int index = 0;

    if (value < 0)
    {
        s[index] = '-';
        value = -value;
        index++;
    }

    int index_pui = 10;

    while (value / index_pui > 9)
        index_pui *= 10;

    while (value > 9)
    {
        s[index] = '0' + value / index_pui;
        value = value % index_pui;
        index_pui /= 10;
        index++;
    }
    s[index] = '0' + value;
    s[index + 1] = '\0';
    return s;
}

static char *handle_year(void)
{
    char *year = malloc(sizeof(char) * 5);

    time_t now;
    time(&now);
    struct tm *time = gmtime(&now);
    return my_itoa(time->tm_year + 1900, year);
}

static char *handle_month(void)
{
    char *month = malloc(sizeof(char) * 3);

    time_t now;
    time(&now);

    struct tm *time = gmtime(&now);

    return my_itoa(time->tm_mon + 1, month);
}

static char *handle_day(void)
{
    char *day = malloc(sizeof(char) * 3);

    time_t now;
    time(&now);
    struct tm *time = gmtime(&now);

    return my_itoa(time->tm_mday, day);
}

static char *concat(char *dest, char *year, int index)
{
    int size = 0;
    while (year[size] != '\0')
        size++;

    if (size == 1)
    {
        dest[index++] = '0';
        dest[index] = year[0];
        return dest;
    }

    int year_ind = 0;
    while (year[year_ind] != '\0')
    {
        dest[index] = year[year_ind];
        index++;
        year_ind++;
    }
    return dest;
}

static void my_free(char *year, char *month, char *day)
{
    free(year);
    free(month);
    free(day);
}

char *date_format(const char *format)
{
    if (valid_string(format) < 0)
        return NULL;

    char *dest = malloc(sizeof(char) * 11);

    char *year = handle_year();
    char *month = handle_month();
    char *day = handle_day();

    int separator = 1;
    int index = 0;
    for (int i = 0; i < 5; i += 2)
    {
        if (format[i] == 'Y')
        {
            dest = concat(dest, year, index);
            index += 4;
        }
        else if (format[i] == 'M')
        {
            dest = concat(dest, month, index);
            index += 2;
        }
        else if (format[i] == 'D')
        {
            dest = concat(dest, day, index);
            index += 2;
        }
        dest[index] = format[separator];
        separator += 2;
        index++;
    }
    my_free(year, month, day);
    return dest;
}
