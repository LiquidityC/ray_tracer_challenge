#include <math.h>
#include "camera.h"
#include "tuple.h"

Camera camera(f32 hs, f32 vs, f32 fov)
{
    f32 half_view = tan(fov/2);
    f32 half_width, half_height;
    f32 aspect = hs / vs;

    if (aspect >= 1) {
        half_width = half_view;
        half_height = half_view / aspect;
    } else {
        half_width = half_view * aspect;
        half_height = half_view;
    }
    return (Camera) {
        .hsize = hs,
        .vsize = vs,
        .fov = fov,
        .transform = IDENTITY,
        .half_width = half_width,
        .half_height = half_height,
        .pixel_size = (half_width * 2) / hs,
    };
}

Ray camera_ray_for_pixel(Camera *c, u32 x, u32 y)
{
    f32 xoffset = (x + 0.5) * c->pixel_size;
    f32 yoffset = (y + 0.5) * c->pixel_size;

    f32 world_x = c->half_width - xoffset;
    f32 world_y = c->half_height - yoffset;

    Mat4 cam_inv = mat4_invert(&c->transform);
    Vec4 pixel = mat4_vector_mul(&cam_inv, &point(world_x, world_y, -1));
    Vec4 origin = mat4_vector_mul(&cam_inv, &ORIGIN);
    Vec4 direction = tuple_sub(&pixel, &origin);
    direction = tuple_normalize(&direction);

    return ray(origin, direction);
}

Canvas camera_render(Camera *camera, World *world)
{
    Canvas image = canvas((u32) camera->hsize, (u32) camera->vsize);
    for (size_t y = 0; y < camera->vsize; ++y) {
        for (size_t x = 0; x < camera->hsize; ++x) {
            Ray r = camera_ray_for_pixel(camera, x, y);
            Color color = world_color_at(world, &r);
            canvas_write_pixel(&image, x, y, &color);
        }
    }
    return image;
}
