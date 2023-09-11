#include "ray.h"

Point ray_position(Ray *r, f32 t)
{
    Vec4 dist = tuple_mul(&r->direction, t);
    return tuple_add(&r->origin, &dist);
}
