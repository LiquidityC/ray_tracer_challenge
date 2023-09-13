#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <stddef.h>
#include "common.h"
#include "matrix.h"

typedef struct Sphere {
    u32 id;
    Mat4 transform;
} Sphere;

Sphere sphere(void);

#endif // _SPHERE_H_

