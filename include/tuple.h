#ifndef _TUPLE_H_
#define _TUPLE_H_

#include <stdbool.h>

typedef union Tuple
{
    struct {
        float x, y, z, w;
    };
    struct {
        float r, g, b, a;
    };
} Tuple;

typedef Tuple Vector;
typedef Tuple Point;
typedef Tuple Color;

#define tuple(x, y, z, w) ((Tuple) { x, y, z, w })
#define point(x, y, z) ((Tuple) { x, y, z, 1.0 })
#define vector(x, y, z) ((Tuple) { x, y, z, 0.0 })
#define color(r, g, b) ((Tuple) { r, g, b, 0.0 })

/**
 * \brief Checks if a tuple is a point
 */
bool tuple_is_point(const Tuple *t);

/**
 * \brief Checks if a tuple is a vector
 */
bool tuple_is_vector(const Tuple *t);

/**
 * \brief Compare two tuples
 */
bool tuple_equal(const Tuple *a, const Tuple *b);

/**
 * \brief Add two tuples
 */
Tuple tuple_add(const Tuple *a, const Tuple *b);

/**
 * \brief Subtract two tuples
 */
Tuple tuple_sub(const Tuple *a, const Tuple *b);

/**
 * \brief Negate a tuple
 */
Tuple tuple_neg(const Tuple *t);

/**
 * \brief Multiply a tuple with a scalar
 */
Tuple tuple_mul(const Tuple *t, float v);

/**
 * \brief Multiple a tuple with a tuple
 */
Tuple tuple_prod(const Tuple *a, const Tuple *b);

/**
 * \brief Divide a tuple with a scalar
 */
Tuple tuple_div(const Tuple *t, float v);

/**
 * \brief Magnitude
 */
float tuple_magnitude(const Tuple *t);

/**
 * \brief Normalize a tuple
 */
Tuple tuple_normalize(const Tuple *t);

/**
 * \brief Tuple dot product
 */
float tuple_dot(const Tuple *a, const Tuple *b);

/**
 * \brief Tuple cross product
 */
Tuple tuple_cross(const Tuple *a, const Tuple *b);

#endif // _TUPLE_H_

