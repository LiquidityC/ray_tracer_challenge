#include <stdio.h>
#include <string.h>
#include "tuple.h"
#include "canvas.h"
#include "matrix.h"

int main(int argc, char **argv)
{
    static const Color FG = color(1, 1, 1);
    static const Color BG = color(0.2, 0.2, 0.2);


    Canvas c = canvas(900, 550);

    /* Set the background */
    for (size_t i = 0; i < c.width; ++i) {
        for (size_t j = 0; j < c.height; ++j) {
            canvas_write_pixel(&c, i, j, &BG);
        }
    }

    Point start = point(0, 1, 0);
    for (size_t i = 0; i < 12; ++i) {
        Transform rot = rotation_z(i * M_PI/6);
        Point hour = mat4_vector_mul(&rot, &start);
        hour = tuple_mul(&hour, 100);
        canvas_write_pixel(&c, 450+hour.x, 225-hour.y, &FG);
    }

    canvas_write_ppm(&c, "clock.ppm");

    canvas_destroy(&c);
    return 0;
}
