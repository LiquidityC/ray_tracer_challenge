#include "sphere.h"
#include <stdio.h>

static u32 _sphere_id = 0;

Sphere sphere(void)
{
    Sphere s = {
        .id = ++_sphere_id,
        .transform = IDENTITY,
    };
    return s;
}

Vec4 sphere_normal_at(const Sphere *s, const Point *world_point)
{
    Transform inverse_transform = mat4_invert(&s->transform);
    Point object_point = mat4_vector_mul(&inverse_transform, world_point);
    Vec4 object_normal = tuple_sub(&object_point, &ORIGIN);
    Mat4 transpose = mat4_transpose(&inverse_transform);
    Vec4 world_normal = mat4_vector_mul(&transpose, &object_normal);
    world_normal.w = 0;
    return tuple_normalize(&world_normal);
}
