#ifndef _TUPLE_H_
#define _TUPLE_H_

#include <stdbool.h>
#include "common.h"

typedef union Tuple
{
    struct {
        f64 x, y, z, w;
    };
    struct {
        f64 r, g, b, a;
    };
    f64 elem[4];
} Tuple;

typedef union Vec3 {
    f64 elem[3];
    struct {
        f64 x, y, z;
    };
} Vec3;

typedef union Vec2 {
    f64 elem[2];
    struct {
        f64 x, y;
    };
} Vec2;

typedef Tuple Vec4;
typedef Tuple Point;
typedef Tuple Color;

#define tuple(x, y, z, w) ((Tuple) { x, y, z, w })
#define point(x, y, z) ((Tuple) { x, y, z, 1.0 })
#define vector(x, y, z) ((Tuple) { x, y, z, 0.0 })
#define color(r, g, b) ((Tuple) { r, g, b, 0.0 })

#define ORIGIN point(0, 0, 0)
#define BLACK color(0, 0, 0)
#define WHITE color(1, 1, 1)

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
#define vec4_equal tuple_equal

/**
 * \brief Compare two Vec3
 */
bool vec3_equal(const Vec3 *a, const Vec3 *b);

/**
 * \brief Compare two Vec2
 */
bool vec2_equal(const Vec2 *a, const Vec2 *b);

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
Tuple tuple_mul(const Tuple *t, f64 v);

/**
 * \brief Multiple a tuple with a tuple
 */
Tuple tuple_prod(const Tuple *a, const Tuple *b);

/**
 * \brief Divide a tuple with a scalar
 */
Tuple tuple_div(const Tuple *t, f64 v);

/**
 * \brief Magnitude
 */
f64 tuple_magnitude(const Tuple *t);

/**
 * \brief Normalize a tuple
 */
Tuple tuple_normalize(const Tuple *t);

/**
 * \brief Tuple dot product
 */
f64 tuple_dot(const Tuple *a, const Tuple *b);

/**
 * \brief Tuple cross product
 */
Tuple tuple_cross(const Tuple *a, const Tuple *b);

/**
 * \brief Reflect a vector against a surface
 */
Tuple tuple_reflect(const Vec4 *v, const Vec4 *normal);

#endif // _TUPLE_H_

