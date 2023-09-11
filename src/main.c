#include <stdio.h>
#include <string.h>
#include "tuple.h"
#include "canvas.h"

typedef struct Projectile {
    Point pos;
    Vec4 vel;
} Projectile;

typedef struct Environment {
    Vec4 gravity;
    Vec4 wind;
} Environment;

static void tick(Environment *env, Projectile *p)
{
    p->pos = tuple_add(&p->pos, &p->vel);

    Vec4 env_factor = tuple_add(&env->gravity, &env->wind);
    p->vel = tuple_add(&p->vel, &env_factor);
}

int main(int argc, char **argv)
{
    static const Color FG = color(1, 1, 1);
    static const Color BG = color(0.2, 0.2, 0.2);

    Point start = point(0, 1, 0);
    Vec4 velocity = tuple_normalize(&vector(1, 1.8, 0));
    velocity = tuple_mul(&velocity, 11.25);

    Projectile p = { start, velocity };
    Environment env = { vector(0, -0.1, 0), vector(-0.01, 0, 0) };

    Canvas c = canvas(900, 550);

    /* Set the background */
    for (size_t i = 0; i < c.width; ++i) {
        for (size_t j = 0; j < c.height; ++j) {
            canvas_write_pixel(&c, i, j, &BG);
        }
    }

    while (p.pos.y >= 0) {
        tick(&env, &p);
        canvas_write_pixel(&c, p.pos.x, c.height - p.pos.y, &FG);
    }

    canvas_write_ppm(&c, "trajectory.ppm");

    canvas_destroy(&c);
    return 0;
}
