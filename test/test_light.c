#include "unity.h"
#include "tuple.h"
#include "light.h"
#include "test_macros.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_point_light(void)
{
    Color intensity = color(1, 1, 1);
    Point position = point(0, 0, 0);
    PointLight light = point_light(position, intensity);
    TEST_ASSERT_EQUAL_VEC4(position, light.position);
    TEST_ASSERT_EQUAL_VEC4(intensity, light.intensity);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_point_light);
    return UNITY_END();
}
