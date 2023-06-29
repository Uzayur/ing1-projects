#include <stdlib.h>

static void terra(char **map, int height, int width)
{
    if (map[height][width] == '#')
        return;

    map[height][width] = '#';
    terra(map, height, width + 1);
    terra(map, height, width - 1);
    terra(map, height + 1, width);
    terra(map, height - 1, width);
}

int lakes(char **map, int width, int height)
{
    int count_lakes = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == '.')
            {
                count_lakes++;
                terra(map, i, j);
            }
        }
    }

    return count_lakes;
}
