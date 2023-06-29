#ifndef MALLOC_H
#define MALLOC_H

#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>

struct data_list
{
    int free;
    size_t size;
    struct data_list *next;
    struct data_list *previous;
};

struct data_head
{
    size_t size;
    struct data_list *data;
    struct data_head *next;
};

void *add_data(size_t size, struct data_head *head);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);

#endif
