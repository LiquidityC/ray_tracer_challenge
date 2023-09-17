#include <stdlib.h>
#include <string.h>
#include "intersection.h"
#include "world.h"

void world_init(World *world)
{
    ol_init(&world->objects);
    ll_init(&world->lights);
}

Color world_color_at(World *w, Ray *r)
{
    Intersects xs = intersect_world(r, w);
    Intersect *hit = intersect_hit(&xs);
    if (hit) {
        IntersectPrecomp comp = intersect_precomp(hit, r);
        return intersect_shade_hit(w, &comp);
    } else {
        return BLACK;
    }
}

void world_destroy(World *world)
{
    ol_destroy(&world->objects);
    ll_destroy(&world->lights);
}
