#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>

#include "my_fnmatch.h"

static int inside(char letter) //check if letter is a symbol
{
	char *symbol = "*?[\\";

	for (int i = 0; i < 4; i++)
	{
		if (symbol[i] == letter)
			return 1;
	}
	return 0;
}

static int interro_point(const char *string, size_t begin) //chech '?' condition
{
	if (string[begin] != '\0')
		return 0;
	return 1;
}

static int my_strlen(const char *string, int string_ind) //length of string from string_ind
{
    int size = 0;
    while (string[string_ind + size] != '\0')
        size++;
    return size;
}

static int include(const char *pattern, const char *string, int begin,
int string_ind)
{//check if a character chain in pattern is include in string
    int index = string_ind;

    int count = begin + 1;
    while((!inside(pattern[count])) && pattern[count] != '\0')
        count++;

    int counter = 0;
    while (string[string_ind] != '\0' && counter != count - begin + 1)
    {
        if (string[index] == pattern[begin + counter])
            counter++;
        else
            counter = 0;
        index++;
    }
    if (counter == count - begin + 1)
        return string_ind + count - begin - 1;
    else
        return 0;
}

static int star(const char *pattern,const char *string, int string_ind,
int pattern_ind) //check '*' condition
{
    if (pattern[pattern_ind + 1] == '\0')
        return string_ind + my_strlen(string, string_ind);

    return include(pattern,string,pattern_ind,string_ind);
}

static int check_hook(const char *pattern, const char *string, int pattern_ind,
int string_ind)
{
    int counter = pattern_ind + 1;
    while (pattern[counter] != ']' && pattern[counter] != '\0' &&
            pattern[counter] != '[')
        counter++;

    if (pattern[counter] == '[')
        return -1;

    else if (pattern[counter] == '\0')
    {
        if (string[string_ind] == '[')
            return 0;
        return -1;
    }

    else if (counter == pattern_ind + 1)
    {
        if (string[string_ind] == '[' && string[string_ind + 1] == ']')
            return 0;
        return -1;
    }
    return hook_calcul(pattern, string, pattern_ind, string_ind);
}

static int hyphen_check(const char *pattern, const char *string, int pattern_ind,
int string_ind)
{
    int pattern_count = pattern_ind + 1;
    while (pattern[pattern_count] != '-')
        pattern_count++;

    char behind = pattern[pattern_count - 1];
    char ahead = pattern[pattern_count + 1];
    if (behind >= ahead && pattern[pattern_ind + 1] != '!')
    {
        if (string[string_ind] <= behind && string[string_ind] >= ahead)
            return pattern_count + 2;
        return -1;
    }
    else if (behind <= ahead && pattern[pattern_ind + 1] != '!')
    {
        if (string[string_ind] >= behind && string[string_ind] <= ahead)
            return pattern_count + 2;
        return -1;
    }
    else if (behind >= ahead && pattern[pattern_ind + 1] == '!')
    {
        if (string[string_ind] <= behind && string[string_ind] >= ahead)
            return -1;
        return pattern_count + 2;
    }
    else
    {
        if (string[string_ind] >= behind && string[string_ind] <= ahead)
            return -1;
        return pattern_count + 2;
    }
}

int hook_calcul(const char *pattern, const char *string, int pattern_ind,
int string_ind)
{
    int hyphen = 0;
    int counter = pattern_ind + 1;
    while (pattern[counter] != ']')
    {
        if (pattern[counter] == '-')
            hyphen++;
        counter++;
    }

    if (hyphen == 0 && pattern[pattern_ind + 1] != '!')
    {
        int pattern_count = pattern_ind + 1;
        while (pattern_count < counter)
        {
            if (string[string_ind] == pattern[pattern_count])
                return counter;
            pattern_count++;
        }
        return -1;
    }
    else if (hyphen == 0 && pattern[pattern_ind + 1] == '!')
    {
        int pattern_count = pattern_ind + 1;
        while (pattern_count < counter)
        {
            if (string[string_ind] == pattern[pattern_count])
                return -1;
            pattern_count++;
        }
        return counter;
    }
    if (hyphen != 0)
        return hyphen_check(pattern,string,pattern_ind, string_ind);
    return 0;
}

int my_fnmatch(const char *pattern, const char *string) //main
{
	size_t string_ind = 0;
	size_t patt_ind = 0;

	while (pattern[patt_ind] != '\0')
	{
		char letter = pattern[patt_ind];
		if (inside(letter))
		{
			if (letter == '?' && interro_point(string, string_ind))
				return 1;
            else if (letter == '*' &&
                    star(pattern,string,string_ind,patt_ind) < 0)
                return 1;
            else if (letter == '*' &&
                    star(pattern,string,string_ind,patt_ind) >= 0)
                string_ind = star(pattern,string,string_ind,patt_ind) - 1;
            else if (letter == '\\' &&
                    pattern[patt_ind + 1] != string[string_ind])
            {
                if (pattern[patt_ind + 1] != string[string_ind])
                    return 1;
                patt_ind += 2;
            }
            else if (letter == '[' &&
                    check_hook(pattern, string, patt_ind, string_ind) < 0)
                return 1;
            else if (letter == '[' &&
                    check_hook(pattern, string, patt_ind, string_ind) > 0)
                patt_ind = check_hook(pattern, string, patt_ind, string_ind);
        }
		else
		{
			if(string[string_ind] != letter)
				return 1;
		}
		string_ind++;
		patt_ind++;
	}
	return 0;
}
