#include "sphere.h"
#include <stdio.h>

static u32 _sphere_id = 0;

Sphere sphere(void)
{
    return ++_sphere_id;
}

Intersects sphere_intersect(Sphere *s, Ray *r)
{
    size_t result = 0;

    Intersects inters;
    intersects_init(&inters);

    /* Ray from sphere center to ray origin */
    Vec4 origin = ORIGIN;
    Vec4 s_to_r = tuple_sub(&r->origin, &origin);

    /* Calculate discriminant */
    f32 a = tuple_dot(&r->direction, &r->direction);
    f32 b = 2.0 * tuple_dot(&r->direction, &s_to_r);
    f32 c = tuple_dot(&s_to_r, &s_to_r) - 1.0;

    f32 discriminant = pow(b, 2) - 4.0 * a * c;

    if (discriminant < 0) {
        goto out;
    }

    f32 t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    f32 t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    intersects_add(&inters, min(t1, t2), *s);
    intersects_add(&inters, max(t1, t2), *s);

out:
    return inters;
}

