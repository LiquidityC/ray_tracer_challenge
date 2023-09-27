#include <stdlib.h>
#include <string.h>
#include "intersection.h"
#include "world.h"
#include "ray.h"

void world_init(World *world)
{
    ol_init(&world->objects);
    ll_init(&world->lights);
}

Color world_color_at(const World *w, const Ray *r)
{
    Intersects xs = intersect_world(r, w);
    Intersect *hit = intersect_hit(&xs);
    Color c = BLACK;
    if (hit) {
        IntersectPrecomp comp = intersect_precomp(hit, r);
        c = intersect_shade_hit(w, &comp);
    }
    intersects_destroy(&xs);
    return c;
}

bool world_is_shadowed(const World *w, size_t light_index, const Point *p)
{
    Vec4 v = tuple_sub(&w->lights.objects[light_index].position, p);
    f64 distance = tuple_magnitude(&v);
    Vec4 direction = tuple_normalize(&v);

    Ray r = ray(*p, direction);
    Intersects xs = intersect_world(&r, w);

    Intersect *hit = intersect_hit(&xs);
    bool result = false;
    if (hit && hit->t < distance) {
        result = true;
    }
    intersects_destroy(&xs);
    return result;
}

void world_destroy(World *world)
{
    ol_destroy(&world->objects);
    ll_destroy(&world->lights);
}
