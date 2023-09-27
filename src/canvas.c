#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"

Canvas canvas(u32 w, u32 h)
{
    Canvas c = {
        .width = w,
        .height = h,
        .grid = calloc(w*h, sizeof(Color)),
    };
    return c;
}

void canvas_write_pixel(Canvas *c, u32 x, u32 y, const Color *color)
{
    if (x >= c->width || x < 0 || y >= c->height || y < 0) {
        return;
    }
    Color *pixel = canvas_get_pixel(c, x, y);
    pixel->x = color->x;
    pixel->y = color->y;
    pixel->z = color->z;
}

Color *canvas_get_pixel(Canvas *c, u32 x, u32 y)
{
    return &c->grid[y * c->width + x];
}

static u32 to_color_octal(f64 val)
{
    u32 color = floor((255.0 * val) + 0.5);
    return clamp(color, 0, 255);
}

i32 canvas_write_ppm(Canvas *c, const char *ppm_path)
{
    FILE *fp = fopen(ppm_path, "w");
    if (!fp) {
        fprintf(stderr, "Failed to open file: %s\n", ppm_path);
        return -1;
    }

    /* Write the header */
    fprintf(fp, "P3\n");
    fprintf(fp, "%u %u\n", c->width, c->height);
    fprintf(fp, "255\n");

    size_t char_count = 0;
    for (size_t i = 0; i < c->width * c->height; ++i) {
        f64 *it = (f64 *) &c->grid[i];
        f64 *end = it + 3;
        while (it != end) {
            char_count += fprintf(fp, "%u", to_color_octal(*it));
            ++it;
            if (char_count > 66) {
                fprintf(fp, "\n");
                char_count = 0;
            } else if (it != end) {
                char_count += fprintf(fp, " ");
            }
        }
        if ((i+1) % c->width == 0) {
            fprintf(fp, "\n");
            char_count = 0;
        } else {
            char_count += fprintf(fp, " ");
        }
    }

    return fclose(fp);
}

void canvas_destroy(Canvas *c)
{
    free(c->grid);
    c->grid = NULL;
}

