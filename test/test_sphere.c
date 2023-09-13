#include "unity.h"
#include "sphere.h"
#include "ray.h"
#include "intersection.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_sphere_default_transform(void)
{
    Sphere s = sphere();
    TEST_ASSERT_TRUE(mat4_equals(&IDENTITY, &s.transform));
}

static void test_change_sphere_transform(void)
{
    Sphere s = sphere();
    s.transform = translation(2, 3, 4);
    Mat4 exp = translation(2, 3, 4);
    TEST_ASSERT_TRUE(mat4_equals(&exp, &s.transform));
}

static void test_scaled_sphere_intersect(void)
{
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    s.transform = scaling(2, 2, 2);
    Intersects xs = intersect_sphere(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(3, intersects_get(&xs, 0)->t);
    TEST_ASSERT_EQUAL_FLOAT(7, intersects_get(&xs, 1)->t);
    intersects_destroy(&xs);
}

static void test_translated_sphere_intersect(void)
{
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    s.transform = translation(5, 0, 0);
    Intersects xs = intersect_sphere(&s, &r);
    TEST_ASSERT_EQUAL_size_t(0, xs.len);
    intersects_destroy(&xs);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sphere_default_transform);
    RUN_TEST(test_scaled_sphere_intersect);
    RUN_TEST(test_translated_sphere_intersect);
    return UNITY_END();
}
