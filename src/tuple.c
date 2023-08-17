#include <stdbool.h>
#include "tuple.h"
#include "float.h"

bool tuple_is_point(Tuple *t)
{
    return t->w == 1.0;
}

bool tuple_is_vector(Tuple *t)
{
    return t->w == 0.0;
}

bool tuple_equal(Tuple *a, Tuple *b)
{
    return fequal(a->x, b->x)
        && fequal(a->y, b->y)
        && fequal(a->z, b->z)
        && fequal(a->w, b->w);
}

Tuple tuple_add(Tuple *a, Tuple *b)
{
    return tuple(a->x + b->x, a->y + b->y, a->z + b->z, a->w + b->w);
}

Tuple tuple_sub(Tuple *a, Tuple *b)
{
    return tuple(a->x - b->x, a->y - b->y, a->z - b->z, a->w - b->w);
}

Tuple tuple_neg(Tuple *t)
{
    return tuple(-t->x, -t->y, -t->z, -t->w);
}

Tuple tuple_mul(Tuple *t, float v)
{
    return tuple(t->x * v, t->y * v, t->z * v, t->w * v);
}

Tuple tuple_div(Tuple *t, float v)
{
    return tuple(t->x / v, t->y / v, t->z / v, t->w / v);
}
