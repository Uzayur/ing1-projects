#include "complex_print.h"

#include <stdio.h>

#include "complex_operations.h"

void print_complex(struct complex a)
{
    if (a.img < 0)
        printf("complex(%.2f - %.2fi)\n", a.real, -a.img);
    else
        printf("complex(%.2f + %.2fi)\n", a.real, a.img);
    return;
}
