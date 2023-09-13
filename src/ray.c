#include "ray.h"

Point ray_position(Ray *r, f32 t)
{
    Vec4 dist = tuple_mul(&r->direction, t);
    return tuple_add(&r->origin, &dist);
}

Ray ray_transform(const Ray *r, const Mat4 *transform)
{
    return ray(
               mat4_vector_mul(transform, &r->origin),
               mat4_vector_mul(transform, &r->direction)
              );
}
