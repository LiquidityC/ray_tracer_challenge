#ifndef _OBJECT_LIST_H_
#define _OBJECT_LIST_H_

#include <stddef.h>
#include "sphere.h"

typedef struct ObjectList {
    size_t len;
    size_t size;
    size_t obj_size;
    Object *objects;
} ObjectList;

void ol_init(ObjectList *ol);

void ol_add(ObjectList *ol, Object o);

bool ol_contains(ObjectList *ol, u32 id);

void ol_destroy(ObjectList *ol);

#endif // _OBJECT_LIST_H_

