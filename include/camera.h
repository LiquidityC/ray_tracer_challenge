#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "matrix.h"
#include "common.h"
#include "ray.h"
#include "canvas.h"
#include "world.h"

typedef struct Camera {
    f64 hsize;
    f64 vsize;
    f64 fov;
    Mat4 transform;
    f64 half_width;
    f64 half_height;
    f64 pixel_size;
} Camera;

Camera camera(f64 hs, f64 vs, f64 fov);

Ray camera_ray_for_pixel(Camera *c, u32 x, u32 y);

Canvas camera_render(Camera *camera, World *world);

#endif // _CAMERA_H_

