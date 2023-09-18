#include <stdio.h>
#include <string.h>
#include "camera.h"
#include "transformation_chain.h"
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

    Sphere floor = sphere();
    floor.transform = scaling(10, 0.01, 10);
    floor.material = material();
    floor.material.color = color(1, 0.9, 0.9);
    floor.material.specular = 0;

    Sphere lwall = sphere();
    chain_begin_mat4(IDENTITY);
    {
        // TODO: These are in reverse compared to examples. Fix it!
        scal(10, 0.01, 10);
        rot_x(M_PI/2);
        rot_y(-M_PI/4);
        trans(0, 0, 5);
    }
    lwall.transform = chain_end_mat4();
    lwall.material = floor.material;

    Sphere rwall = sphere();
    chain_begin_mat4(IDENTITY);
    {
        scal(10, 0.01, 10);
        rot_x(M_PI/2);
        rot_y(M_PI/4);
        trans(0, 0, 5);
    }
    rwall.transform = chain_end_mat4();
    rwall.material = floor.material;

    Sphere middle = sphere();
    middle.transform = translation(-0.5, 1, 0.5);
    middle.material = material();
    middle.material.color = color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right = sphere();
    chain_begin_mat4(IDENTITY);
    {
        scal(0.5, 0.5, 0.5);
        trans(1.5, 0.5, -0.5);
    }
    right.transform = chain_end_mat4();
    right.material = material();
    right.material.color = color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left = sphere();
    chain_begin_mat4(IDENTITY);
    {
        scal(0.33, 0.33, 0.33);
        trans(-1.5, 0.33, -0.75);
    }
    left.transform = chain_end_mat4();
    right.material.color = color(1, 0.8, 1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    PointLight light = point_light(point(-10, 10, -10), color(1, 1, 1));

    World world;
    world_init(&world);

    ll_add(&world.lights, light);
    ol_add(&world.objects, lwall);
    ol_add(&world.objects, rwall);
    ol_add(&world.objects, floor);
    ol_add(&world.objects, left);
    ol_add(&world.objects, right);
    ol_add(&world.objects, middle);

    Camera cam = camera(800, 800, M_PI/3);
    cam.transform = mat4_view_transform(&point(0, 1.5, -5), &point(0, 1, 0), &point(0, 1, 0));

    Canvas image = camera_render(&cam, &world);
    canvas_write_ppm(&image, "world.ppm");
    canvas_destroy(&image);
    world_destroy(&world);

    return 0;
}
