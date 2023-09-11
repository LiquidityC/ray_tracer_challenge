#include "sphere.h"

static u32 _sphere_id = 0;

Sphere sphere(void)
{
    return ++_sphere_id;
}

size_t sphere_intersect(Sphere *s, Ray *r, f32 *xs)
{
    Vec4 origin = ORIGIN;
    Vec4 s_to_r = tuple_sub(&r->origin, &origin);

    // TODO: Continue here

    return 0;
}

