#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "common.h"
#include "tuple.h"

typedef struct Canvas {
    u32 width;
    u32 height;
    Color *grid;
} Canvas;

/**
 * \brief Construct a canvas
 */
Canvas canvas(u32 w, u32 h);

/**
 * \brief Write a pixel to the canvas
 */
void canvas_write_pixel(Canvas *c, u32 x, u32 y, const Color *color);

/**
 * \brief Read a pixel from the canvas
 */
Color *canvas_get_pixel(Canvas *c, u32 x, u32 y);

/**
 * \brief Write the canvas out as a PPM file
 */
i32 canvas_write_ppm(Canvas *c, const char *ppm_path);

/**
 * \brief Destroy a canvas
 */
void canvas_destroy(Canvas *c);

#endif // _CANVAS_H_

