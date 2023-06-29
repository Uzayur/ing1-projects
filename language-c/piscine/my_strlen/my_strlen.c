#include <stddef.h>

size_t my_strlen(const char *s)
{
    size_t compteur = 0;

    while (s[compteur] != '\0')
        compteur++;

    return compteur;
}
