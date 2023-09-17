#include <stdio.h>
#include <stdlib.h>
#include "object_list.h"

void ol_init(ObjectList *ol)
{
    ol->len = 0;
    ol->size = 1;
    ol->objects = calloc(ol->size, sizeof(Object));
}

static void ol_expand_if_needed(ObjectList *ol)
{
    if (ol->len < ol->size) {
        return;
    }

    Object *new_obj = realloc(ol->objects, ol->size*2*sizeof(Object));
    if (new_obj == NULL) {
        perror("realloc");
        return;
    }
    ol->objects = new_obj;
    ol->size *= 2;
}

void ol_add(ObjectList *ol, Object o)
{
    ol_expand_if_needed(ol);
    ol->objects[ol->len++] = o;
}

bool ol_contains(ObjectList *ol, u32 id)
{
    for (size_t i = 0; i < ol->len; ++i) {
        Object *it = ol->objects + i;
        if (it->id == id) {
            return true;
        }
    }
    return false;
}

void ol_destroy(ObjectList *ol)
{
    free(ol->objects);
}
