#include "sphere.h"
#include <stdio.h>

static u32 _sphere_id = 0;

Sphere sphere(void)
{
    Sphere s = {
        .id = ++_sphere_id,
        .transform = IDENTITY,
    };
    return s;
}
