#include "unity.h"
#include "material.h"
#include "test_macros.h"
#include "light.h"

Material m;
Point position;

void setUp(void)
{
    m = material();
    position = point(0, 0, 0);
}

void tearDown(void)
{
}

static void test_material(void)
{
    TEST_ASSERT_EQUAL_VEC4(color(1, 1, 1), m.color);
}

static void test_eye_between_light_and_surface(void)
{
    Vec4 eyev = vector(0, 0, -1);
    Vec4 normalv = vector(0, 0, -1);
    PointLight light = point_light(point(0, 0, -10), color(1, 1, 1));
    Color result = material_lighting(&m, &light, &position, &eyev, &normalv, false);
    TEST_ASSERT_EQUAL_COLOR(color(1.9, 1.9, 1.9), result);
}

static void test_eye_between_light_and_surface_offset_45(void)
{
    Vec4 eyev = vector(0, sqrt(2)/2, -sqrt(2)/2);
    Vec4 normalv = vector(0, 0, -1);
    PointLight light = point_light(point(0, 0, -10), color(1, 1, 1));
    Color result = material_lighting(&m, &light, &position, &eyev, &normalv, false);
    TEST_ASSERT_EQUAL_COLOR(color(1.0, 1.0, 1.0), result);
}

static void test_eye_opposite_surface_light_offset_45(void)
{
    Vec4 eyev = vector(0, 0, -1);
    Vec4 normalv = vector(0, 0, -1);
    PointLight light = point_light(point(0, 10, -10), color(1, 1, 1));
    Color result = material_lighting(&m, &light, &position, &eyev, &normalv, false);
    TEST_ASSERT_EQUAL_COLOR(color(0.7364, 0.7364, 0.7364), result);
}

static void test_eye_opposite_light_both_offset_45(void)
{
    Vec4 eyev = vector(0, -sqrt(2)/2, -sqrt(2)/2);
    Vec4 normalv = vector(0, 0, -1);
    PointLight light = point_light(point(0, 10, -10), color(1, 1, 1));
    Color result = material_lighting(&m, &light, &position, &eyev, &normalv, false);
    TEST_ASSERT_EQUAL_COLOR(color(1.6364, 1.6364, 1.6364), result);
}

static void test_light_behind_surface(void)
{
    Vec4 eyev = vector(0, 0, -1);
    Vec4 normalv = vector(0, 0, -1);
    PointLight light = point_light(point(0, 0, 10), color(1, 1, 1));
    Color result = material_lighting(&m, &light, &position, &eyev, &normalv, false);
    TEST_ASSERT_EQUAL_COLOR(color(0.1, 0.1, 0.1), result);
}

static void test_in_shadow(void)
{
    Vec4 eyev = vector(0, 0, -1);
    Vec4 normalv = vector(0, 0, -1);
    PointLight light = point_light(point(0, 0, -10), color(1, 1, 1));
    bool in_shadow = true;
    Color result = material_lighting(&m, &light, &position, &eyev, &normalv, in_shadow);
    TEST_ASSERT_EQUAL_COLOR(color(0.1, 0.1, 0.1), result);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_material);
    RUN_TEST(test_eye_between_light_and_surface);
    RUN_TEST(test_eye_between_light_and_surface_offset_45);
    RUN_TEST(test_eye_opposite_surface_light_offset_45);
    RUN_TEST(test_eye_opposite_light_both_offset_45);
    RUN_TEST(test_light_behind_surface);
    RUN_TEST(test_in_shadow);
    return UNITY_END();
}
