#include "allocator.h"

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

struct blk_allocator *blka_new(void)
{
    struct blk_allocator *new_struct = malloc(sizeof(struct blk_allocator));

    if (!new_struct)
        return NULL;
    new_struct->meta = NULL;
    return new_struct;
}

#include <stdio.h>
void blka_delete(struct blk_allocator *blka)
{
    if (!blka)
        return;

    struct blk_meta *tmp;

    while (blka->meta != NULL)
    {
        tmp = blka->meta->next;
        free(blka->meta);
        blka->meta = tmp;
    }
    free(blka);
}

struct blk_meta *blka_alloc(struct blk_allocator *blka, size_t size)
{
    struct blk_meta *new =
        mmap(NULL, sizeof(struct blk_meta), PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    new->size = size;
    new->next = blka->meta;

    blka->meta = new;

    return new;
}

void blka_free(struct blk_meta *blk)
{
    munmap(blk, sizeof(struct blk_meta));
}

void blka_pop(struct blk_allocator *blka)
{
    if (!blka->meta || !blka)
        return;

    struct blk_meta *head = blka->meta->next;
    blka->meta->next = NULL;
    free(blka->meta);
    blka->meta = head;
}

#include <stdio.h>
int main(void)
{
    struct blk_meta *test_meta2 = malloc(sizeof(struct blk_meta));
    test_meta2->size = 90;
    test_meta2->next = NULL;

    struct blk_allocator *test = malloc(sizeof(struct blk_allocator));
    test->meta = test_meta2;

    /*
    printf("%ld %ld\n", test->meta->size, test->meta->next->size);
    blka_pop(test);
    printf("%ld\n", test->meta->size);
    if (!test->meta->next)
        printf("OK");

    free(test_meta);
    free(test);
    */
    struct blk_meta *test_meta = blka_alloc(test, 8);
    printf("%ld\n", test_meta->size);
    blka_delete(test);

    return 0;
}
