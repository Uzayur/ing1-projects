#include <stddef.h>

void rot_x(char *s, int x)
{
    if (s == NULL)
        return;
    else
    {
        int indice = 0;
        while (s[indice] != '\0')
            indice++;

        for (int i = 0; i < indice; i++)
        {
            int letter = s[i];
            if (letter > 64 && letter < 91)
                if ((letter - 65) + x < 0)
                    s[i] = 65 + (((letter - 65) + x + 26) % 26);
                else
                    s[i] = 65 + (((letter - 65) + x) % 26);
            else if (letter > 96 && letter < 123)
                if ((letter - 97) + x < 0)
                    s[i] = 97 + (((letter - 97) + x + 26) % 26);
                else
                    s[i] = 97 + (((letter - 97) + x) % 26);
            else
                s[i] = letter;
        }
        return;
    }
}
