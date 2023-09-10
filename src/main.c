#include <stdio.h>
#include "tuple.h"

typedef struct Projectile {
    Point pos;
    Vector vel;
} Projectile;

typedef struct Environment {
    Vector gravity;
    Vector wind;
} Environment;

static void tick(Environment *env, Projectile *p)
{
    p->pos = tuple_add(&p->pos, &p->vel);

    Vector env_factor = tuple_add(&env->gravity, &env->wind);
    p->vel = tuple_add(&p->vel, &env_factor);
}

int main(int argc, char **argv)
{
    Projectile p = { point(0, 1, 0), tuple_normalize(&vector(1, 1, 0)) };
    Environment env = { vector(0, -0.1, 0), vector(-0.01, 0, 0) };

    while (p.pos.y >= 0) {
        tick(&env, &p);
        printf("%.2f %.2f\n", p.pos.x, p.pos.y);
    }
    return 0;
}
