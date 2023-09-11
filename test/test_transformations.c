#include "unity.h"
#include "matrix.h"
#include "transformation_chain.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_transform_point(void)
{
    Transform transform = translation(5, -3, 2);
    Point p = point(-3, 4, 5);
    Point res = mat4_vector_mul(&transform, &p);
    Point exp = point(2, 1, 7);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &res));
}

static void test_transform_point_invert(void)
{
    Transform transform = translation(5, -3, 2);
    Transform inv = mat4_invert(&transform);
    Point p = point(-3, 4, 5);
    Point res = mat4_vector_mul(&inv, &p);
    Point exp = point(-8, 7, 3);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &res));
}

static void test_transform_vector(void)
{
    Transform transform = translation(5, -3, 2);
    Vec4 v = vector(-3, 4, 5);
    Vec4 res = mat4_vector_mul(&transform, &v);
    TEST_ASSERT_TRUE(tuple_equal(&v, &res));
}

static void test_scaling_point(void)
{
    Transform transform = scaling(2, 3, 4);
    Point p = point(-4, 6, 8);
    Point exp = point(-8, 18, 32);
    Point res = mat4_vector_mul(&transform, &p);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &res));
}

static void test_scaling_vector(void)
{
    Transform transform = scaling(2, 3, 4);
    Vec4 v = vector(-4, 6, 8);
    Vec4 exp = vector(-8, 18, 32);
    Vec4 res = mat4_vector_mul(&transform, &v);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &res));
}

static void test_scaling_inverse(void)
{
    Transform transform = scaling(2, 3, 4);
    Transform inv = mat4_invert(&transform);
    Vec4 v = vector(-4, 6, 8);
    Vec4 exp = vector(-2, 2, 2);
    Vec4 res = mat4_vector_mul(&inv, &v);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &res));
}

static void test_reflection(void)
{
    Transform transform = scaling(-1, 1, 1);
    Point p = point(2, 3, 4);
    Point exp = point(-2, 3, 4);
    Point res = mat4_vector_mul(&transform, &p);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &res));
}

static void test_x_rotation(void)
{
    Point p = point(0, 1, 0);
    Transform half_quarter = rotation_x(M_PI/4);
    Transform full_quarter = rotation_x(M_PI/2);
    Point exp1 = point(0, sqrt(2)/2, sqrt(2)/2);
    Point exp2 = point(0, 0, 1);
    Point res1 = mat4_vector_mul(&half_quarter, &p);
    Point res2 = mat4_vector_mul(&full_quarter, &p);
    TEST_ASSERT_TRUE(tuple_equal(&exp1, &res1));
    TEST_ASSERT_TRUE(tuple_equal(&exp2, &res2));
}

static void test_x_inverse_rotation(void)
{
    Point p = point(0, 1, 0);
    Transform half_quarter = rotation_x(M_PI/4);
    Transform inv = mat4_invert(&half_quarter);
    Point exp = point(0, sqrt(2)/2, -(sqrt(2)/2));
    Point res = mat4_vector_mul(&inv, &p);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &res));
}

static void test_y_rotation(void)
{
    Point p = point(0, 0, 1);
    Transform half_quarter = rotation_y(M_PI/4);
    Transform full_quarter = rotation_y(M_PI/2);
    Point exp1 = point(sqrt(2)/2, 0, sqrt(2)/2);
    Point exp2 = point(1, 0, 0);
    Point res1 = mat4_vector_mul(&half_quarter, &p);
    Point res2 = mat4_vector_mul(&full_quarter, &p);
    TEST_ASSERT_TRUE(tuple_equal(&exp1, &res1));
    TEST_ASSERT_TRUE(tuple_equal(&exp2, &res2));
}

static void test_z_rotation(void)
{
    Point p = point(0, 1, 0);
    Transform half_quarter = rotation_z(M_PI/4);
    Transform full_quarter = rotation_z(M_PI/2);
    Point exp1 = point(-sqrt(2)/2, sqrt(2)/2, 0);
    Point exp2 = point(-1, 0, 0);
    Point res1 = mat4_vector_mul(&half_quarter, &p);
    Point res2 = mat4_vector_mul(&full_quarter, &p);
    TEST_ASSERT_TRUE(tuple_equal(&exp1, &res1));
    TEST_ASSERT_TRUE(tuple_equal(&exp2, &res2));
}

static void test_shearing(void)
{
    Transform xy = shearing(1, 0, 0, 0, 0, 0);
    Transform xz = shearing(0, 1, 0, 0, 0, 0);
    Transform yx = shearing(0, 0, 1, 0, 0, 0);
    Transform yz = shearing(0, 0, 0, 1, 0, 0);
    Transform zx = shearing(0, 0, 0, 0, 1, 0);
    Transform zy = shearing(0, 0, 0, 0, 0, 1);

    Point p = point(2, 3, 4);

    Point res_xy = mat4_vector_mul(&xy, &p);
    Point exp_xy = point(5, 3, 4);
    TEST_ASSERT_TRUE(tuple_equal(&exp_xy, &res_xy));

    Point res_xz = mat4_vector_mul(&xz, &p);
    Point exp_xz = point(6, 3, 4);
    TEST_ASSERT_TRUE(tuple_equal(&exp_xz, &res_xz));

    Point res_yx = mat4_vector_mul(&yx, &p);
    Point exp_yx = point(2, 5, 4);
    TEST_ASSERT_TRUE(tuple_equal(&exp_yx, &res_yx));

    Point res_yz = mat4_vector_mul(&yz, &p);
    Point exp_yz = point(2, 7, 4);
    TEST_ASSERT_TRUE(tuple_equal(&exp_yz, &res_yz));

    Point res_zx = mat4_vector_mul(&zx, &p);
    Point exp_zx = point(2, 3, 6);
    TEST_ASSERT_TRUE(tuple_equal(&exp_zx, &res_zx));

    Point res_zy = mat4_vector_mul(&zy, &p);
    Point exp_zy = point(2, 3, 7);
    TEST_ASSERT_TRUE(tuple_equal(&exp_zy, &res_zy));
}

static void test_individual_transformations(void)
{
    Point p= point(1, 0, 1);
    Transform rot = rotation_x(M_PI/2);
    Transform scale = scaling(5, 5, 5);
    Transform translate = translation(10, 5, 7);

    Point p2 = mat4_vector_mul(&rot, &p);
    Point exp = point(1, -1, 0);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &p2));

    Point p3 = mat4_vector_mul(&scale, &p2);
    exp = point(5, -5, 0);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &p3));

    Point p4 = mat4_vector_mul(&translate, &p3);
    exp = point(15, 0, 7);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &p4));
}

static void test_chain_transformations(void)
{
    chain_begin_vec4(point(1, 0, 1));
    {
        rot_x(M_PI/2);
        scal(5, 5, 5);
        trans(10, 5, 7);
    }
    Point p = chain_end_vec4();
    Point exp = point(15, 0, 7);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &p));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_transform_point);
    RUN_TEST(test_transform_point_invert);
    RUN_TEST(test_transform_vector);
    RUN_TEST(test_scaling_point);
    RUN_TEST(test_scaling_vector);
    RUN_TEST(test_scaling_inverse);
    RUN_TEST(test_reflection);
    RUN_TEST(test_x_rotation);
    RUN_TEST(test_x_inverse_rotation);
    RUN_TEST(test_y_rotation);
    RUN_TEST(test_z_rotation);
    RUN_TEST(test_shearing);
    RUN_TEST(test_individual_transformations);
    RUN_TEST(test_chain_transformations);
    return UNITY_END();
}
