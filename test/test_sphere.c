#include "unity.h"
#include "sphere.h"
#include "ray.h"
#include "intersection.h"
#include "transformation_chain.h"

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

static void test_normal_on_x_axis(void)
{
    Sphere s = sphere();
    Vec4 n = sphere_normal_at(&s, &point(1, 0, 0));
    Vec4 exp = vector(1, 0, 0);
    TEST_ASSERT_TRUE(vec4_equal(&exp, &n));
}

static void test_normal_on_y_axis(void)
{
    Sphere s = sphere();
    Vec4 n = sphere_normal_at(&s, &point(0, 1, 0));
    Vec4 exp = vector(0, 1, 0);
    TEST_ASSERT_TRUE(vec4_equal(&exp, &n));
}

static void test_normal_on_z_axis(void)
{
    Sphere s = sphere();
    Vec4 n = sphere_normal_at(&s, &point(0, 0, 1));
    Vec4 exp = vector(0, 0, 1);
    TEST_ASSERT_TRUE(vec4_equal(&exp, &n));
}

static void test_normal_on_nonaxial_point(void)
{
    Sphere s = sphere();
    Vec4 n = sphere_normal_at(&s, &point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    Vec4 exp = vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    TEST_ASSERT_TRUE(vec4_equal(&exp, &n));
}

static void test_normal_is_normalized(void)
{
    Sphere s = sphere();
    Vec4 n = sphere_normal_at(&s, &point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    Vec4 exp = tuple_normalize(&n);
    TEST_ASSERT_TRUE(vec4_equal(&exp, &n));
}

static void test_normal_on_translated_sphere(void)
{
    Sphere s = sphere();
    s.transform = translation(0, 1, 0);
    Vec4 n = sphere_normal_at(&s, &point(0, 1.70711, -0.70711));
    Vec4 exp = vector(0, 0.70711, -0.70711);
    TEST_ASSERT_TRUE(vec4_equal(&exp, &n));
}

static void test_normal_on_transformed_sphere(void)
{
    Sphere s = sphere();
    s.transform = mat4_mul(&scaling(1, 0.5, 1), &rotation_z(M_PI/5));
    Vec4 n = sphere_normal_at(&s, &point(0, sqrt(2)/2, -sqrt(2)/2));
    Vec4 exp = vector(0, 0.97014, -0.24254);
    TEST_ASSERT_TRUE(vec4_equal(&exp, &n));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sphere_default_transform);
    RUN_TEST(test_scaled_sphere_intersect);
    RUN_TEST(test_translated_sphere_intersect);
    RUN_TEST(test_normal_on_x_axis);
    RUN_TEST(test_normal_on_y_axis);
    RUN_TEST(test_normal_on_z_axis);
    RUN_TEST(test_normal_on_nonaxial_point);
    RUN_TEST(test_normal_is_normalized);
    RUN_TEST(test_normal_on_translated_sphere);
    RUN_TEST(test_normal_on_transformed_sphere);
    return UNITY_END();
}
