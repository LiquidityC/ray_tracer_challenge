#ifndef _WORLD_H_
#define _WORLD_H_

#include "light_list.h"
#include "sphere.h"
#include "object_list.h"
#include "tuple.h"
#include "ray.h"

typedef struct World {
    ObjectList objects;
    LightList lights;
} World;

void world_init(World *world);

Color world_color_at(const World *w, const Ray *r);

bool world_is_shadowed(const World *w, size_t light_index, const Point *p);

void world_destroy(World *world);

#endif // _WORLD_H_

