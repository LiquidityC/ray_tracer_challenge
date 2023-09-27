#include <stdbool.h>
#include <math.h>
#include <stddef.h>
#include "tuple.h"
#include "float.h"

bool tuple_is_point(const Tuple *t)
{
    return t->w == 1.0;
}

bool tuple_is_vector(const Tuple *t)
{
    return t->w == 0.0;
}

static bool vector_equal(const f64 *a, const f64 *b, size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        if (!fequal(*(a + i), *(b + i))) {
            return false;
        }
    }
    return true;
}

bool tuple_equal(const Tuple *a, const Tuple *b)
{
    return vector_equal(&a->elem[0], &b->elem[0], 4);
}

bool vec3_equal(const Vec3 *a, const Vec3 *b)
{
    return vector_equal(&a->elem[0], &b->elem[0], 3);
}

bool vec2_equal(const Vec2 *a, const Vec2 *b)
{
    return vector_equal(&a->elem[0], &b->elem[0], 2);
}

Tuple tuple_add(const Tuple *a, const Tuple *b)
{
    return tuple(a->x + b->x, a->y + b->y, a->z + b->z, a->w + b->w);
}

Tuple tuple_sub(const Tuple *a, const Tuple *b)
{
    return tuple(a->x - b->x, a->y - b->y, a->z - b->z, a->w - b->w);
}

Tuple tuple_neg(const Tuple *t)
{
    return tuple(-t->x, -t->y, -t->z, -t->w);
}

Tuple tuple_mul(const Tuple *t, f64 v)
{
    return tuple(t->x * v, t->y * v, t->z * v, t->w * v);
}

Tuple tuple_div(const Tuple *t, f64 v)
{
    return tuple(t->x / v, t->y / v, t->z / v, t->w / v);
}

Tuple tuple_prod(const Tuple *a, const Tuple *b)
{
    return color(a->r * b->r, a->g * b->g, a->b * b->b);
}

f64 tuple_magnitude(const Tuple *t)
{
    return sqrt(pow(t->x, 2) + pow(t->y, 2) + pow(t->z, 2) + pow(t->w, 2));
}

Tuple tuple_normalize(const Tuple *t)
{
    f64 magnitude = tuple_magnitude(t);
    return tuple(t->x / magnitude,
                 t->y / magnitude,
                 t->z / magnitude,
                 t->w / magnitude);
}

f64 tuple_dot(const Tuple *a, const Tuple *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

Tuple tuple_cross(const Tuple *a, const Tuple *b)
{
    return vector(a->y * b->z - a->z * b->y,
                  a->z * b->x - a->x * b->z,
                  a->x * b->y - a->y * b->x);
}

Tuple tuple_reflect(const Vec4 *v, const Vec4 *normal)
{
    Vec4 mul = tuple_mul(normal, 2 * tuple_dot(v, normal));
    return tuple_sub(v, &mul);
}
