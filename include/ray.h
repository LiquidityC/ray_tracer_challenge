#ifndef _RAY_H_
#define _RAY_H_

#include <stddef.h>

#include "matrix.h"
#include "tuple.h"
#include "common.h"

typedef struct Ray {
    Point origin;
    Vec4 direction;
} Ray;

#define ray(o, d) ((Ray) { o, d })

/**
 * \brief Calculate a position along the ray after t time has passed
 */
Point ray_position(const Ray *r, f64 t);

/**
 * \brief Transform a ray
 */
Ray ray_transform(const Ray *r, const Mat4 *transform);

#endif // _RAY_H_

