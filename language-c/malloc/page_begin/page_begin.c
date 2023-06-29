#include "page_begin.h"

#include <stdio.h>

void *page_begin(void *ptr, size_t page_size)
{
    page_size--;
    char *acu = ptr;
    size_t test = (size_t)ptr & page_size;

    return acu - test;
}
