#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "matrix.h"
#include "common.h"
#include "ray.h"
#include "canvas.h"
#include "world.h"

typedef struct Camera {
    f32 hsize;
    f32 vsize;
    f32 fov;
    Mat4 transform;
    f32 half_width;
    f32 half_height;
    f32 pixel_size;
} Camera;

Camera camera(f32 hs, f32 vs, f32 fov);

Ray camera_ray_for_pixel(Camera *c, u32 x, u32 y);

Canvas camera_render(Camera *camera, World *world);

#endif // _CAMERA_H_

