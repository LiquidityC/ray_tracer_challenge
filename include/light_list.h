#ifndef _LIGHT_LIST_H_
#define _LIGHT_LIST_H_

#include <stddef.h>
#include "light.h"

typedef struct LightList {
    size_t len;
    size_t size;
    size_t obj_size;
    PointLight *objects;
} LightList;

void ll_init(LightList *ll);

void ll_add(LightList *ll, PointLight o);

void ll_destroy(LightList *ll);

#endif // _LIGHT_LIST_H_

