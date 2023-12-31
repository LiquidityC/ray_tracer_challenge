#include "intersection.h"
#include "ray.h"
#include "unity.h"
#include "world.h"
#include "test_macros.h"
#include "utils.h"

void setUp(void) { }

void tearDown(void) { }

static void test_empty_world(void)
{
    World w;
    world_init(&w);
    TEST_ASSERT_EQUAL_size_t(0, w.objects.len);
    TEST_ASSERT_EQUAL_size_t(0, w.lights.len);
    world_destroy(&w);
}

static void test_world_with_objects(void)
{
    World w = default_world();

    PointLight wl = w.lights.objects[0];
    PointLight light = point_light(point(-10, 10, -10), color(1, 1, 1));
    TEST_ASSERT_EQUAL_POINTLIGHT(light, wl);

    Sphere s1 = sphere();
    s1.material.color = color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    ol_add(&w.objects, s1);

    Sphere s2 = sphere();
    s2.transform = scaling(0.5, 0.5, 0.5);
    ol_add(&w.objects, s2);

    Sphere ws1 = w.objects.objects[0];
    TEST_ASSERT_EQUAL_SPHERE(s1, ws1);

    Sphere ws2 = w.objects.objects[1];
    TEST_ASSERT_EQUAL_SPHERE(s2, ws2);

    world_destroy(&w);
}

static void test_world_intersect(void)
{
    World w = default_world();
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Intersects xs = intersect_world(&r, &w);

    TEST_ASSERT_EQUAL_size_t(4, xs.len);
    TEST_ASSERT_EQUAL_DOUBLE(4, intersects_get(&xs, 0)->t);
    TEST_ASSERT_EQUAL_DOUBLE(4.5, intersects_get(&xs, 1)->t);
    TEST_ASSERT_EQUAL_DOUBLE(5.5, intersects_get(&xs, 2)->t);
    TEST_ASSERT_EQUAL_DOUBLE(6, intersects_get(&xs, 3)->t);

    intersects_destroy(&xs);
    world_destroy(&w);
}

static void test_world_shade_intersection(void)
{
    World w = default_world();
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere *s = &w.objects.objects[0];
    Intersect i = intersect(4, s);
    IntersectPrecomp comps = intersect_precomp(&i, &r);
    Color c = intersect_shade_hit(&w, &comps);
    TEST_ASSERT_EQUAL_COLOR(color(0.38066, 0.47583, 0.2854959), c);
    world_destroy(&w);
}

static void test_world_shade_inside_intersection(void)
{
    World w = default_world();
    w.lights.objects[0] = point_light(point(0, 0.25, 0), color(1, 1, 1));
    Ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    Sphere *s = &w.objects.objects[1];
    Intersect i = intersect(0.5, s);
    IntersectPrecomp comps = intersect_precomp(&i, &r);
    Color c = intersect_shade_hit(&w, &comps);
    TEST_ASSERT_EQUAL_COLOR(color(0.90498, 0.90498, 0.90498), c);
    world_destroy(&w);
}

static void test_world_color_at_miss(void)
{
    World w = default_world();
    Ray r = ray(point(0, 0, -5), vector(0, 1, 0));
    Color c = world_color_at(&w, &r);
    TEST_ASSERT_EQUAL_COLOR(color(0, 0, 0), c);
}

static void test_world_color_at_hit(void)
{
    World w = default_world();
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Color c = world_color_at(&w, &r);
    TEST_ASSERT_EQUAL_COLOR(color(0.38066, 0.47583, 0.2854959), c);
}

static void test_world_color_at_when_intersect_behind(void)
{
    World w = default_world();
    Object *outer = &w.objects.objects[0];
    outer->material.ambient = 1;
    Object *inner = &w.objects.objects[1];
    inner->material.ambient = 1;
    Ray r = ray(point(0, 0, 0.75), vector(0, 0, -1));
    Color c = world_color_at(&w, &r);
    TEST_ASSERT_EQUAL_COLOR(inner->material.color, c);
}

static void test_world_is_shadowed_nothing_blocking(void)
{
    World w = default_world();
    Point p = point(0, 10, 0);
    TEST_ASSERT_FALSE(world_is_shadowed(&w, 0, &p));
}

static void test_world_is_shadowed_sphere_blocking(void)
{
    World w = default_world();
    Point p = point(10, -10, 10);
    TEST_ASSERT_TRUE(world_is_shadowed(&w, 0, &p));
}

static void test_world_is_shadowed_point_behind_light(void)
{
    World w = default_world();
    Point p = point(-20, 20, -20);
    TEST_ASSERT_FALSE(world_is_shadowed(&w, 0, &p));
}

static void test_world_is_shadowed_point_between(void)
{
    World w = default_world();
    Point p = point(-2, 2, -2);
    TEST_ASSERT_FALSE(world_is_shadowed(&w, 0, &p));
}

static void test_world_shade_hit_shadow(void)
{
    World w;
    world_init(&w);
    ll_add(&w.lights, point_light(point(0, 0, -10), color(1, 1, 1)));

    Object s1 = sphere();
    ol_add(&w.objects, s1);
    Object s2 = sphere();
    s2.transform = translation(0, 0, 10);
    ol_add(&w.objects, s2);

    Ray r = ray(point(0, 0, 5), vector(0, 0, 1));
    Intersect x = intersect(4, &s2);
    IntersectPrecomp comp = intersect_precomp(&x, &r);
    Color result = intersect_shade_hit(&w, &comp);
    TEST_ASSERT_EQUAL_COLOR(color(0.1, 0.1, 0.1), result);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_empty_world);
    RUN_TEST(test_world_with_objects);
    RUN_TEST(test_world_intersect);
    RUN_TEST(test_world_shade_intersection);
    RUN_TEST(test_world_shade_inside_intersection);
    RUN_TEST(test_world_color_at_miss);
    RUN_TEST(test_world_color_at_hit);
    RUN_TEST(test_world_color_at_when_intersect_behind);
    RUN_TEST(test_world_color_at_when_intersect_behind);
    RUN_TEST(test_world_is_shadowed_nothing_blocking);
    RUN_TEST(test_world_is_shadowed_sphere_blocking);
    RUN_TEST(test_world_is_shadowed_point_behind_light);
    RUN_TEST(test_world_is_shadowed_point_between);
    RUN_TEST(test_world_shade_hit_shadow);
    return UNITY_END();
}
