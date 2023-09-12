#include <stdio.h>
#include <stdlib.h>
#include "intersection.h"

static int intersects_extend(Intersects *xs)
{
    Intersect *new_inters = realloc(xs->xs, 2 * xs->size * sizeof(Intersect));
    if (!new_inters) {
        return -1;
    }
    xs->xs = new_inters;
    xs->size *= 2;
    return 0;
}

void intersects_init(Intersects *xs)
{
    xs->len = 0;
    xs->size = 1;
    xs->xs = malloc(sizeof(Intersect));
}

void intersects_add(Intersects *xs, f32 t, f32 object)
{
    if (xs->size - 1 == xs->len) {
        if (intersects_extend(xs) != 0) {
            perror("intersects_extend");
            return;
        }
    }
    xs->xs[xs->len++] = (Intersect) { t, object };
}

void intersects_push(Intersects *xs, Intersect x)
{
    if (xs->size - 1 == xs->len) {
        if (intersects_extend(xs) != 0) {
            perror("intersects_extend");
            return;
        }
    }
    xs->xs[xs->len++] = x;
}

Intersects intersects(int n, ...)
{
    // TODO: This needs to sort on insert
    Intersects xs;
    intersects_init(&xs);

    va_list ptr;
    va_start(ptr, n);
    for (size_t i = 0; i < n; ++i) {
        intersects_push(&xs, va_arg(ptr, Intersect));
    }
    va_end(ptr);

    return xs;
}

Intersect* intersect_hit(const Intersects *xs)
{
    if (xs->len == 0) {
        return NULL;
    }

    Intersect *hit = xs->xs;
    for (size_t i = 1; i < xs->len; ++i) {
        f32 t = xs->xs[i].t;
        if (hit->t < 0) {
            hit = xs->xs + i;
        }
        if (t > 0 && t < hit->t) {
            hit = xs->xs + i;
        }
    }
    if (hit->t < 0) {
        hit = NULL;
    }
    return hit;
}

bool intersect_equal(const Intersect *a, const Intersect *b)
{
    return a->t == b->t && a->object == b->object;
}

void intersects_destroy(Intersects *xs)
{
    if (xs->xs != NULL) {
        free(xs->xs);
    }
    xs->xs = NULL;
}
