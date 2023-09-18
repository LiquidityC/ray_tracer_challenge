#include "utils.h"

World default_world(void)
{
    World w;
    world_init(&w);
    ll_add(&w.lights, point_light(point(-10, 10, -10), color(1, 1, 1)));

    Sphere s1 = sphere();
    s1.material.color = color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    ol_add(&w.objects, s1);

    Sphere s2 = sphere();
    s2.transform = scaling(0.5, 0.5, 0.5);
    ol_add(&w.objects, s2);

    return w;
}

