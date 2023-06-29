#include "evalexpr.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valid_operator(char s)
{
    char *symbol = "()+-/%*^";

    int index = 0;
    while (symbol[index] != '\0')
    {
        if (s == symbol[index])
            return 1;
        index++;
    }
    return 0;
}

static int check_number(char *input, int begin)
{
    int end = begin;
    while (input[end] >= 48 && input[end] <= 57)
        end++;

    char *number = malloc(sizeof(char) * end - begin + 3);
    int index_number = 0;
    while (begin <= end)
    {
        number[index_number] = input[begin];
        index_number++;
        begin++;
    }
    return atoi(number);
}

static int right_index(char *input, int begin)
{
    int end = begin;
    while (input[end] >= 48 && input[end] <= 57)
        end++;
    return end;
}

struct stack
{
    int top_int;
    char top_char;
    struct stack *next;
};

static struct stack *push_int(struct stack *s, int elem)
{
    struct stack *new_stack = malloc(sizeof(struct stack));
    if (!new_stack)
        return s;

    new_stack->top_int = elem;
    new_stack->next = s;

    return new_stack;
}

static struct stack *push_char(struct stack *s, char elem)
{
    struct stack *new_stack = malloc(sizeof(struct stack));
    if (!new_stack)
        return s;

    new_stack->top_char = elem;
    new_stack->next = s;

    return new_stack;
}

static int calcul_number(int number1, int number2, char operator)
{
    if (operator== '+')
        return number1 + number2;
    else if (operator== '-')
        return number2 - number1;
    else if (operator== '*')
        return number1 * number2;
    else if (operator== '/')
    {
        if (number2 == 0)
            return -3789;
        return number1 / number2;
    }
    else if (operator== '%')
    {
        if (number2 == 0)
            return -3789;
        return number1 % number2;
    }
    else
    {
        int res = 1;
        for (int i = 0; i < number1; i++)
            res *= number2;
        return res;
    }
}

static int calcul_rpn(char *input)
{
    size_t input_index = 0;

    struct stack *calcul = malloc(sizeof(struct stack));

    while (input_index < strlen(input))
    {
        char letter = input[input_index];
        if (letter >= 48 && letter <= 57)
        {
            calcul = push_int(calcul, check_number(input, input_index));
            input_index = right_index(input, input_index) - 1;
        }
        else if (valid_operator(letter) == 1)
        {
            if (!calcul->next)
                return -3789;
            else
            {
                int number1 = calcul->top_int;
                int number2 = calcul->next->top_int;
                calcul = calcul->next;

                if (calcul_number(number1, number2, letter) == -3789)
                    return -3789;
                calcul->top_int = calcul_number(number1, number2, letter);
            }
        }
        input_index++;
    }
    return calcul->top_int;
}

static int convert_rpn(char *input)
{
    char *copy_input = malloc(sizeof(char) * 100);
    int copy_index = 0;
    size_t input_index = 0;

    struct stack *copy = malloc(sizeof(struct stack));

    while (input_index != strlen(input) - 1)
    {
        char letter = input[input_index];
        if (letter >= '0' && letter <= '9')
        {
            copy_input[copy_index] = letter;
            copy_index++;
        }

        else if (valid_operator(letter) == 1)
            copy = push_char(copy, letter);

        else
        {
            copy_input[copy_index] = letter;
            copy_index++;
        }

        input_index++;
    }
    while (copy->next)
    {
        copy_input[copy_index] = copy->top_char;
        copy_index++;
        copy = copy->next;
    }
    copy_input[copy_index] = copy->top_char;
    return calcul_rpn(copy_input);
}

int main(int argc, char *argv[])
{
    char *input = malloc(sizeof(char) * 100);
    fread(input, sizeof(char), 90, stdin);

    if ((argc == 2 && strcmp("-rpn", argv[1]) != 0) || argc > 2)
        return 4;

    size_t index = 0;
    while (index != strlen(input) - 1)
    {
        char letter = input[index];
        if ((letter > 57 || letter < 48) && valid_operator(letter) == 0
            && letter != ' ')
            return 1;

        else if (input[index] == '(')
        {
            int index_test = index;
            while (input[index_test] != '(' && input[index_test] != '\0')
                index_test++;
            if (index_test - index < 4 || input[index_test] == '\0')
                return 2;
        }
        else if (input[index] == ')')
            return 2;
        index++;
    }
    if (argc == 2)
    {
        if (calcul_rpn(input) == -3789)
            return 2;
        printf("%d\n", calcul_rpn(input));
    }
    else
        printf("%d\n", convert_rpn(input));
    return 0;
}
