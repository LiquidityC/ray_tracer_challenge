#include "unity.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"

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
    Intersects xs = intersect_sphere(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_DOUBLE(4, intersects_get(&xs, 0)->t);
    TEST_ASSERT_EQUAL_DOUBLE(6, intersects_get(&xs, 1)->t);
    intersects_destroy(&xs);
}

static void test_ray_sphere_glance(void)
{
    Ray r = ray(point(0, 1, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = intersect_sphere(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_DOUBLE(5, intersects_get(&xs, 0)->t);
    TEST_ASSERT_EQUAL_DOUBLE(5, intersects_get(&xs, 1)->t);
    intersects_destroy(&xs);
}

static void test_ray_sphere_miss(void)
{
    Ray r = ray(point(0, 2, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = intersect_sphere(&s, &r);
    TEST_ASSERT_EQUAL_size_t(0, xs.len);
    intersects_destroy(&xs);
}

static void test_ray_sphere_inside(void)
{
    Ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = intersect_sphere(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_DOUBLE(-1, intersects_get(&xs, 0)->t);
    TEST_ASSERT_EQUAL_DOUBLE(1, intersects_get(&xs, 1)->t);
    intersects_destroy(&xs);
}

static void test_ray_sphere_behind(void)
{
    Ray r = ray(point(0, 0, 5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = intersect_sphere(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_DOUBLE(-6, intersects_get(&xs, 0)->t);
    TEST_ASSERT_EQUAL_DOUBLE(-4, intersects_get(&xs, 1)->t);
    intersects_destroy(&xs);
}

static void test_translating_ray(void)
{
    Ray r = ray(point(1, 2, 3), vector(0, 1, 0));
    Transform t = translation(3, 4, 5);
    Ray res = ray_transform(&r, &t);
    Point oexp = point(4, 6, 8);
    Vec4 vexp = vector(0, 1, 0);
    TEST_ASSERT_TRUE(vec4_equal(&oexp, &res.origin));
    TEST_ASSERT_TRUE(vec4_equal(&vexp, &res.direction));
}

static void test_scaling_ray(void)
{
    Ray r = ray(point(1, 2, 3), vector(0, 1, 0));
    Transform t = scaling(2, 3, 4);
    Ray res = ray_transform(&r, &t);
    Point oexp = point(2, 6, 12);
    Vec4 vexp = vector(0, 3, 0);
    TEST_ASSERT_TRUE(vec4_equal(&oexp, &res.origin));
    TEST_ASSERT_TRUE(vec4_equal(&vexp, &res.direction));
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
    RUN_TEST(test_translating_ray);
    RUN_TEST(test_scaling_ray);
    return UNITY_END();
}
