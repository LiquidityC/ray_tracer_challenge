#include <stdbool.h>
#include <math.h>
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

bool tuple_equal(const Tuple *a, const Tuple *b)
{
    return fequal(a->x, b->x)
        && fequal(a->y, b->y)
        && fequal(a->z, b->z)
        && fequal(a->w, b->w);
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

Tuple tuple_mul(const Tuple *t, float v)
{
    return tuple(t->x * v, t->y * v, t->z * v, t->w * v);
}

Tuple tuple_div(const Tuple *t, float v)
{
    return tuple(t->x / v, t->y / v, t->z / v, t->w / v);
}

float tuple_magnitude(const Tuple *t)
{
    return sqrt(pow(t->x, 2) + pow(t->y, 2) + pow(t->z, 2) + pow(t->w, 2));
}

Tuple tuple_normalize(const Tuple *t)
{
    float magnitude = tuple_magnitude(t);
    return tuple(t->x / magnitude,
                 t->y / magnitude,
                 t->z / magnitude,
                 t->w / magnitude);
}

float tuple_dot(const Tuple *a, const Tuple *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

Tuple tuple_cross(const Tuple *a, const Tuple *b)
{
    return tuple(1, 2, 3, 1);
}
