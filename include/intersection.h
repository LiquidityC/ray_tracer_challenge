#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include "common.h"
#include "sphere.h"
#include "ray.h"
#include "world.h"

typedef struct Intersect {
    f64 t;
    const Object *object;
} Intersect;

typedef struct IntersectPrecomp {
    f64 t;
    const Object *object;
    Point point;
    Point over_point;
    Vec4 eyev;
    Vec4 normalv;
    bool inside;
} IntersectPrecomp;

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

Intersects intersects_new(f64 t, f64 o);

void intersects_add(Intersects *xs, f64 t, const Object *object);

void intersects_push(Intersects *xs, Intersect x);

void intersects_merge(Intersects *xs, const Intersects *other);

Intersect* intersects_get(const Intersects *xs, size_t index);

Intersect* intersect_hit(const Intersects *xs);

Color intersect_shade_hit(const World *w, const IntersectPrecomp *comp);

bool intersect_equal(const Intersect *a, const Intersect *b);

void intersects_destroy(Intersects *xs);

IntersectPrecomp intersect_precomp(const Intersect *i, const Ray *r);

/**
 * \brief Find intersections between a ray and a sphere's 'hull'
 */
Intersects intersect_sphere(const Sphere *s, const Ray *r);

Intersects intersect_world(const Ray *r, const World *w);


#endif // _INTERSECTION_H_

