#include "unity.h"
#include "ray.h"
#include "sphere.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_ray(void)
{
    Point origin = point(1, 2, 3);
    Vec4 direction = vector(4, 5, 6);
    Ray ray = ray(origin, direction);

    TEST_ASSERT_TRUE(vec4_equal(&origin, &ray.origin));
    TEST_ASSERT_TRUE(vec4_equal(&direction, &ray.direction));
}

static void test_ray_point_from_distance(void)
{
    Ray r = ray(point(2, 3, 4), vector(1, 0, 0));

    Point p1 = ray_position(&r, 0);
    Point e1 = point(2, 3, 4);
    TEST_ASSERT_TRUE(vec4_equal(&e1, &p1));

    Point p2 = ray_position(&r, 1);
    Point e2 = point(3, 3, 4);
    TEST_ASSERT_TRUE(vec4_equal(&e2, &p2));

    Point p3 = ray_position(&r, -1);
    Point e3 = point(1, 3, 4);
    TEST_ASSERT_TRUE(vec4_equal(&e3, &p3));

    Point p4 = ray_position(&r, 2.5);
    Point e4 = point(4.5, 3, 4);
    TEST_ASSERT_TRUE(vec4_equal(&e4, &p4));
}

static void test_ray_sphere_intersection(void)
{
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    f32 xs[2];
    size_t count = sphere_intersect(&s, &r, xs);
    TEST_ASSERT_EQUAL_size_t(2, count);
    TEST_ASSERT_EQUAL_FLOAT(4, xs[0]);
    TEST_ASSERT_EQUAL_FLOAT(6, xs[1]);
}

static void test_ray_sphere_glance(void)
{
    Ray r = ray(point(0, 1, -5), vector(0, 0, 1));
    Sphere s = sphere();
    f32 xs[2];
    size_t count = sphere_intersect(&s, &r, xs);
    TEST_ASSERT_EQUAL_size_t(2, count);
    TEST_ASSERT_EQUAL_FLOAT(5, xs[0]);
    TEST_ASSERT_EQUAL_FLOAT(5, xs[1]);
}

static void test_ray_sphere_miss(void)
{
    Ray r = ray(point(0, 2, -5), vector(0, 0, 1));
    Sphere s = sphere();
    f32 xs[2];
    size_t count = sphere_intersect(&s, &r, xs);
    TEST_ASSERT_EQUAL_size_t(0, count);
}

static void test_ray_sphere_inside(void)
{
    Ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = sphere();
    f32 xs[2];
    size_t count = sphere_intersect(&s, &r, xs);
    TEST_ASSERT_EQUAL_size_t(2, count);
    TEST_ASSERT_EQUAL_FLOAT(-1, xs[0]);
    TEST_ASSERT_EQUAL_FLOAT(1, xs[1]);
}

static void test_ray_sphere_behind(void)
{
    Ray r = ray(point(0, 0, 5), vector(0, 0, 1));
    Sphere s = sphere();
    f32 xs[2];
    size_t count = sphere_intersect(&s, &r, xs);
    TEST_ASSERT_EQUAL_size_t(2, count);
    TEST_ASSERT_EQUAL_FLOAT(-6, xs[0]);
    TEST_ASSERT_EQUAL_FLOAT(-4, xs[1]);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ray);
    RUN_TEST(test_ray_point_from_distance);
    RUN_TEST(test_ray_sphere_intersection);
    RUN_TEST(test_ray_sphere_glance);
    RUN_TEST(test_ray_sphere_miss);
    RUN_TEST(test_ray_sphere_inside);
    RUN_TEST(test_ray_sphere_behind);
    return UNITY_END();
}
