#include <stdio.h>
#include <string.h>
#include "tuple.h"
#include "canvas.h"
#include "matrix.h"
#include "sphere.h"
#include "ray.h"
#include "intersection.h"

int main(int argc, char **argv)
{
    static const Color FG = color(0, 1, 0);
    static const Color BG = color(0.2, 0.2, 0.2);

    f32 canvas_dim = 100;
    Canvas c = canvas(canvas_dim, canvas_dim);
    Sphere s = sphere();

    f32 wall_z = 10;
    f32 wall_size = 7;
    f32 pixel_size = wall_size / canvas_dim;
    f32 half = wall_size / 2;
    Point origin = point(0, 0, -5);

    for (size_t y = 0; y < canvas_dim; ++y) {
        f32 world_y = half - pixel_size * y;
        for (size_t x = 0; x < canvas_dim; ++x) {
            f32 world_x = -half + pixel_size * x;
            Point dest = point(world_x, world_y, wall_z);
            Vec4 dir = tuple_sub(&dest, &origin);
            dir = tuple_normalize(&dir);
            Ray r = ray(origin, dir);
            Intersects xs = intersect_sphere(&s, &r);
            if (intersect_hit(&xs)) {
                canvas_write_pixel(&c, x, y, &FG);
            } else {
                canvas_write_pixel(&c, x, y, &BG);
            }
            intersects_destroy(&xs);
        }
    }

    canvas_write_ppm(&c, "sphere.ppm");

    canvas_destroy(&c);
    return 0;
}
