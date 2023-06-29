#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

struct vector *vector_init(size_t n)
{
    struct vector *vec = malloc(sizeof(struct vector));

    if (!vec)
        return NULL;

    vec->data = malloc(sizeof(int) * n);
    vec->capacity = n;
    vec->size = 0;
    return vec;
}

void vector_destroy(struct vector *v)
{
    free(v->data);
    free(v);
}

struct vector *vector_resize(struct vector *v, size_t n)
{
    if (n == v->capacity)
        return v;

    v->data = realloc(v->data, sizeof(int) * n);
    v->capacity = n;

    if (v->size > v->capacity)
        v->size = v->capacity;

    return v;
}

struct vector *vector_append(struct vector *v, int elt)
{
    if (!v)
        return NULL;

    if (v->size < v->capacity)
    {
        v->data[v->size] = elt;
        v->size += 1;
    }
    else
    {
        v->data = realloc(v->data, sizeof(int) * v->capacity * 2);
        v->data[v->size] = elt;
        v->capacity = v->capacity * 2;
        v->size += 1;
    }
    return v;
}

void vector_print(const struct vector *v)
{
    if (!v || v->size == 0)
    {
        printf("\n");
        return;
    }
    for (size_t i = 0; i < v->size; ++i)
    {
        if (i == v->size - 1)
            printf("%d\n", v->data[i]);
        else
            printf("%d,", v->data[i]);
    }
}

struct vector *vector_reset(struct vector *v, size_t n)
{
    free(v->data);

    v->size = 0;
    v->capacity = n;
    v->data = malloc(sizeof(int) * n);

    if (!v->data)
        return NULL;

    return v;
}

struct vector *vector_insert(struct vector *v, size_t i, int elt)
{
    if (!v || v->size < i)
        return NULL;

    if (v->size == i)
        return vector_append(v, elt);

    else
    {
        if (v->size == v->capacity)
        {
            v->data = realloc(v->data, sizeof(int) * (v->capacity * 2));

            if (!v->data)
                return NULL;

            v->capacity = v->capacity * 2;
        }

        size_t index = v->size;
        while (index != i)
        {
            int tmp = v->data[i];
            v->data[index] = v->data[index - 1];
            v->data[index - 1] = tmp;
            index--;
        }
        v->data[index] = elt;

        v->size += 1;

        return v;
    }
}

struct vector *vector_remove(struct vector *v, size_t i)
{
    if (!v)
        return NULL;

    if (i >= v->size)
        return NULL;

    while (i != v->size - 1)
    {
        v->data[i] = v->data[i + 1];
        i++;
    }

    v->size -= 1;

    if (v->size < v->capacity / 2)
        vector_resize(v, v->capacity / 2);

    return v;
}
