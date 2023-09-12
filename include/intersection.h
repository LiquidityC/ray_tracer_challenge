#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include "common.h"

typedef struct Intersect {
    f32 t;
    f32 object;
} Intersect;

#define intersect(t, o) ((Intersect) { t, o })

typedef struct Intersects {
    size_t len;
    size_t size;
    Intersect *xs;
} Intersects;

void intersects_init(Intersects *xs);

Intersects intersects(int n, ...);

Intersects intersects_new(f32 t, f32 o);

void intersects_add(Intersects *xs, f32 t, f32 object);

void intersects_push(Intersects *xs, Intersect x);

void intersects_destroy(Intersects *xs);

Intersect* intersect_hit(const Intersects *xs);

bool intersect_equal(const Intersect *a, const Intersect *b);

#endif // _INTERSECTION_H_

