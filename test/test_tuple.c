#include "unity.h"
#include "tuple.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_tuple_is_point(void)
{
    Tuple t = { 4.3, -4.2, 3.1, 1.0 };
    TEST_ASSERT_EQUAL_FLOAT(4.3, t.x);
    TEST_ASSERT_EQUAL_FLOAT(-4.2, t.y);
    TEST_ASSERT_EQUAL_FLOAT(3.1, t.z);
    TEST_ASSERT_EQUAL_FLOAT(1.0, t.w);
}

void test_tuple_is_vector(void)
{
    Tuple t = { 4.3, -4.2, 3.1, 0.0 };
    TEST_ASSERT_EQUAL_FLOAT(4.3, t.x);
    TEST_ASSERT_EQUAL_FLOAT(-4.2, t.y);
    TEST_ASSERT_EQUAL_FLOAT(3.1, t.z);
    TEST_ASSERT_EQUAL_FLOAT(0.0, t.w);
}

void test_factory_functions(void)
{
    Tuple p = point(4, -4, 3);
    TEST_ASSERT_TRUE(tuple_equal(&p, &tuple(4, -4, 3, 1)));

    Tuple v = vector(4, -4, 3);
    TEST_ASSERT_TRUE(tuple_equal(&v, &tuple(4, -4, 3, 0)));
}

void test_addition(void)
{
    Tuple a = tuple(3, -2, 5, 1);
    Tuple b = tuple(-2, 3, 1, 0);
    Tuple r = tuple_add(&a, &b);
    TEST_ASSERT_TRUE(tuple_equal(&r, &tuple(1, 1, 6, 1)));
}

void test_subtraction(void)
{
    Tuple a = point(3, 2, 1);
    Tuple b = point(5, 6, 7);
    Tuple r = tuple_sub(&a, &b);
    TEST_ASSERT_TRUE(tuple_equal(&r, &vector(-2, -4, -6)));

    Tuple p = point(3, 2, 1);
    Tuple v = vector(5, 6, 7);
    r = tuple_sub(&p, &v);
    TEST_ASSERT_TRUE(tuple_equal(&r, &point(-2, -4, -6)));

    Tuple v1 = vector(3, 2, 1);
    Tuple v2 = vector(5, 6, 7);
    r = tuple_sub(&v1, &v2);
    TEST_ASSERT_TRUE(tuple_equal(&r, &vector(-2, -4, -6)));

    v1 = vector(0, 0, 0);
    v2 = vector(1, -2, 3);
    r = tuple_sub(&v1, &v2);
    TEST_ASSERT_TRUE(tuple_equal(&r, &vector(-1, 2, -3)));
}

void test_negate(void)
{
    Tuple t = tuple(1, -2, 3, -4);
    Tuple n = tuple_neg(&t);
    TEST_ASSERT_TRUE(tuple_equal(&n, &tuple(-1, 2, -3, 4)));
}

void test_multiply(void)
{
    Tuple t = tuple(1, -2, 3, -4);
    Tuple r = tuple_mul(&t, 0.5);
    TEST_ASSERT_TRUE(tuple_equal(&r, &tuple(0.5, -1, 1.5, -2)));
}

void test_divide(void)
{
    Tuple t = tuple(1, -2, 3, -4);
    Tuple r = tuple_div(&t, 2);
    TEST_ASSERT_TRUE(tuple_equal(&r, &tuple(0.5, -1, 1.5, -2)));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_tuple_is_point);
    RUN_TEST(test_tuple_is_vector);
    RUN_TEST(test_factory_functions);
    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);
    RUN_TEST(test_negate);
    RUN_TEST(test_multiply);
    RUN_TEST(test_divide);
    return UNITY_END();
}