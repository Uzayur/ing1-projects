#include <stddef.h>

static int check_line(char *game[], size_t line, size_t columns, char piece)
{
    int counter_connect4 = 0;
    int counter_piece = 0;

    for (size_t j = 0; j <= columns; j++)
    {
        if (game[line][j] == piece)
            counter_piece++;

        if (counter_piece >= 4 && game[line][j] != piece)
        {
            counter_connect4++;
            counter_piece = 0;
        }

        else if (game[line][j] != piece)
            counter_piece = 0;
    }
    return counter_connect4;
}

static int check_column(char *game[], size_t column, size_t lines, char piece)
{
    int counter_connect4 = 0;
    int counter_piece = 0;

    for (size_t i = 0; i < lines; i++)
    {
        if (game[i][column] == piece)
            counter_piece++;

        else if (counter_piece >= 4 && game[i][column] != piece)
        {
            counter_connect4++;
            counter_piece = 0;
        }

        else
            counter_piece = 0;
    }
    if (counter_piece >= 4)
        counter_connect4++;

    return counter_connect4;
}

static int check_diags_top_left(char *game[], size_t columns, size_t lines,
                                char piece)
{
    int counter_connect4 = 0;
    for (size_t j = 0; j < columns - 3; j++)
    {
        size_t line = 0;
        size_t column = j;
        int counter_piece = 0;

        while (line != lines && column != columns)
        {
            if (game[line][column] == piece)
                counter_piece++;

            else if (counter_piece >= 4)
            {
                counter_connect4++;
                counter_piece = 0;
            }

            else
                counter_piece = 0;
            line++;
            column++;
        }
        if (counter_piece >= 4)
            counter_connect4++;
    }
    return counter_connect4;
}

static int check_diags_bottom_left(char *game[], size_t columns, size_t lines,
                                   char piece)
{
    int counter_connect4 = 0;
    for (size_t i = 1; i < lines - 3; i++)
    {
        size_t line = i;
        size_t column = 0;
        int counter_piece = 0;

        while (line != lines && column != columns)
        {
            if (game[line][column] == piece)
                counter_piece++;

            else if (counter_piece >= 4)
            {
                counter_connect4++;
                counter_piece = 0;
            }

            else
                counter_piece = 0;
            line++;
            column++;
        }
        if (counter_piece >= 4)
            counter_connect4++;
    }
    return counter_connect4;
}

static int check_diags_top_right(char *game[], size_t columns, size_t lines,
                                 char piece)
{
    int counter_connect4 = 0;
    for (size_t j = columns - 1; j > 2; j--)
    {
        int counter_piece = 0;
        size_t line = 0;
        int column = j;

        while (line != lines && column >= 0)
        {
            if (game[line][column] == piece)
                counter_piece++;

            else if (counter_piece >= 4)
            {
                counter_connect4++;
                counter_piece = 0;
            }

            else
                counter_piece = 0;
            line++;
            column--;
        }
        if (counter_piece >= 4)
            counter_connect4++;
    }
    return counter_connect4;
}

static int check_diags_bottom_right(char *game[], size_t columns, size_t lines,
                                    char piece)
{
    int counter_connect4 = 0;
    for (size_t i = 1; i < lines - 3; i++)
    {
        int counter_piece = 0;
        size_t line = i;
        size_t column = columns - 1;

        while (line != lines && column != 0)
        {
            if (game[line][column] == piece)
                counter_piece++;

            else if (counter_piece >= 4)
            {
                counter_connect4++;
                counter_piece = 0;
            }

            else
                counter_piece = 0;
            line++;
            column--;
        }
        if (counter_piece >= 4)
            counter_connect4++;
    }
    return counter_connect4;
}

int connect4(char *game[], size_t columns, size_t lines)
{
    int player_1 = 0;
    int player_2 = 0;

    for (size_t i = 0; i < lines; i++)
    {
        player_1 += check_line(game, i, columns, 'X');
        player_2 += check_line(game, i, columns, 'O');
    }
    for (size_t j = 0; j < columns; j++)
    {
        player_1 += check_column(game, j, lines, 'X');
        player_2 += check_column(game, j, lines, 'O');
    }
    player_1 += check_diags_top_left(game, columns, lines, 'X');
    player_2 += check_diags_top_left(game, columns, lines, 'O');

    player_1 += check_diags_bottom_left(game, columns, lines, 'X');
    player_2 += check_diags_bottom_left(game, columns, lines, 'O');

    player_1 += check_diags_top_right(game, columns, lines, 'X');
    player_2 += check_diags_top_right(game, columns, lines, 'O');

    player_1 += check_diags_bottom_right(game, columns, lines, 'X');
    player_2 += check_diags_bottom_right(game, columns, lines, 'O');

    if (player_1 + player_2 == 0 || player_1 + player_2 > 1)
        return 0;
    else if (player_1 == 1)
        return 1;
    return 2;
}
