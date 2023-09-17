#include <stdio.h>
#include <stdlib.h>
#include "light_list.h"

void ll_init(LightList *ll)
{
    ll->len = 0;
    ll->size = 1;
    ll->objects = calloc(ll->size, sizeof(PointLight));
}

static void ll_expand_if_needed(LightList *ll)
{
    if (ll->len < ll->size) {
        return;
    }

    PointLight *new_obj = realloc(ll->objects, ll->size*2*sizeof(PointLight));
    if (new_obj == NULL) {
        perror("realloc");
        return;
    }
    ll->objects = new_obj;
    ll->size *= 2;
}

void ll_add(LightList *ll, PointLight o)
{
    ll_expand_if_needed(ll);
    ll->objects[ll->len++] = o;
}

void ll_destroy(LightList *ll)
{
    free(ll->objects);
}
