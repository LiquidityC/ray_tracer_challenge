#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <stddef.h>
#include "common.h"
#include "ray.h"

typedef u32 Sphere;

Sphere sphere(void);

/**
 * \brief Find intersections between a ray and a sphere's 'hull'
 */
size_t sphere_intersect(Sphere *s, Ray *r, f32 *xs);

#endif // _SPHERE_H_

