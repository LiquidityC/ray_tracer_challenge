#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include "common.h"
#include "sphere.h"
#include "ray.h"

typedef struct Intersect {
    f32 t;
    f32 object;
} Intersect;

#define intersect(t, o) ((Intersect) { t, o })

typedef struct IntersectsNode {
    Intersect x;
    struct IntersectsNode *next;
} Xsn;

typedef struct Intersects {
    size_t len;
    Xsn *head;
} Intersects;

void intersects_init(Intersects *xs);

Intersects intersects(int n, ...);

Intersects intersects_new(f32 t, f32 o);

void intersects_add(Intersects *xs, f32 t, f32 object);

void intersects_push(Intersects *xs, Intersect x);

Intersect* intersects_get(const Intersects *xs, size_t index);

Intersect* intersect_hit(const Intersects *xs);

bool intersect_equal(const Intersect *a, const Intersect *b);

void intersects_destroy(Intersects *xs);

/**
 * \brief Find intersections between a ray and a sphere's 'hull'
 */
Intersects intersect_sphere(Sphere *s, Ray *r);


#endif // _INTERSECTION_H_

