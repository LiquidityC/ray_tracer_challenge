#include "unity.h"
#include "tuple.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_reflecting_vector(void)
{
    Vec4 v = vector(1, -1, 0);
    Vec4 n = vector(0, 1, 0);
    Vec4 r = tuple_reflect(&v, &n);
    Vec4 exp = vector(1, 1, 0);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &r));
}

static void test_reflecting_slanted_surface(void)
{
    Vec4 v = vector(0, -1, 0);
    Vec4 n = vector(sqrt(2)/2, sqrt(2)/2, 0);
    Vec4 r = tuple_reflect(&v, &n);
    Vec4 exp = vector(1, 0, 0);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &r));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_reflecting_vector);
    RUN_TEST(test_reflecting_slanted_surface);
    return UNITY_END();
}
