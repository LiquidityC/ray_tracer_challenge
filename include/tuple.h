#ifndef _TUPLE_H_
#define _TUPLE_H_

#include <stdbool.h>

typedef struct Tuple
{
    float x, y, z, w;
} Tuple;

#define tuple(x, y, z, w) ((Tuple) { x, y, z, w })
#define point(x, y, z) ((Tuple) { x, y, z, 1.0 })
#define vector(x, y, z) ((Tuple) { x, y, z, 0.0 })

/**
 * \brief Checks if a tuple is a point
 */
bool tuple_is_point(Tuple *t);

/**
 * \brief Checks if a tuple is a vector
 */
bool tuple_is_vector(Tuple *t);

/**
 * \brief Compare two tuples
 */
bool tuple_equal(Tuple *a, Tuple *b);

/**
 * \brief Add two tuples
 */
Tuple tuple_add(Tuple *a, Tuple *b);

/**
 * \brief Subtract two tuples
 */
Tuple tuple_sub(Tuple *a, Tuple *b);

/**
 * \brief Negate a tuple
 */
Tuple tuple_neg(Tuple *t);

/**
 * \brief Multiply a tuple with a scalar
 */
Tuple tuple_mul(Tuple *t, float v);

/**
 * \brief Divide a tuple with a scalar
 */
Tuple tuple_div(Tuple *t, float v);

#endif // _TUPLE_H_

