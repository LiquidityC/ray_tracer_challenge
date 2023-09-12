#include "sphere.h"
#include <stdio.h>

static u32 _sphere_id = 0;

Sphere sphere(void)
{
    return ++_sphere_id;
}

size_t sphere_intersect(Sphere *s, Ray *r, f32 *xs)
{
    size_t result = 0;

    /* Ray from sphere center to ray origin */
    Vec4 origin = ORIGIN;
    Vec4 s_to_r = tuple_sub(&r->origin, &origin);

    /* Calculate discriminant */
    f32 a = tuple_dot(&r->direction, &r->direction);
    f32 b = 2.0 * tuple_dot(&r->direction, &s_to_r);
    f32 c = tuple_dot(&s_to_r, &s_to_r) - 1.0;

    printf("%.2f %.2f %.2f\n", a, b, c);
    f32 discriminant = pow(b, 2) - 4.0 * a * c;

    if (discriminant < 0) {
        goto out;
    }

    f32 t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    f32 t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    xs[0] = min(t1, t2);
    xs[1] = max(t1, t2);

    result = 2;
out:
    return result;
}

