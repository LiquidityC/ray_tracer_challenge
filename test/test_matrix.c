#include "matrix.h"
#include "unity.h"
#include "tuple.h"

void setUp(void) {}

void tearDown(void) {}

static void test_matrix_create(void) {
    {
        Mat4 m = {{
            {1, 2, 3, 4},
            {5.5, 6.5, 7.5, 8.5},
            {9, 10, 11, 12},
            {13.5, 14.5, 15.5, 16.5},
        }};

        TEST_ASSERT_EQUAL_FLOAT(1, m.elem[0][0]);
        TEST_ASSERT_EQUAL_FLOAT(4, m.elem[0][3]);
        TEST_ASSERT_EQUAL_FLOAT(5.5, m.elem[1][0]);
        TEST_ASSERT_EQUAL_FLOAT(7.5, m.elem[1][2]);
        TEST_ASSERT_EQUAL_FLOAT(11, m.elem[2][2]);
        TEST_ASSERT_EQUAL_FLOAT(13.5, m.elem[3][0]);
        TEST_ASSERT_EQUAL_FLOAT(15.5, m.elem[3][2]);
    }

    {
        Mat2 m = {{
            { -3, 5 },
            { 1, -2 },
        }};

        TEST_ASSERT_EQUAL_FLOAT(-3, m.elem[0][0]);
        TEST_ASSERT_EQUAL_FLOAT(5, m.elem[0][1]);
        TEST_ASSERT_EQUAL_FLOAT(1, m.elem[1][0]);
        TEST_ASSERT_EQUAL_FLOAT(-2, m.elem[1][1]);
    }

    {
        Mat3 m = {{
            { -3, 5, 0 },
            { 1, -2, -7 },
            { 0, 1, 1 },
        }};

        TEST_ASSERT_EQUAL_FLOAT(-3, m.elem[0][0]);
        TEST_ASSERT_EQUAL_FLOAT(5, m.elem[0][1]);
        TEST_ASSERT_EQUAL_FLOAT(1, m.elem[1][0]);
        TEST_ASSERT_EQUAL_FLOAT(-2, m.elem[1][1]);
        TEST_ASSERT_EQUAL_FLOAT(1, m.elem[2][2]);
    }
}

static void test_matrix_equality(void)
{
    Mat4 a = {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 8, 7, 6 },
        { 5, 4, 3, 2 },
    }};
    Mat4 b = {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 8, 7, 6 },
        { 5, 4, 3, 2 },
    }};

    TEST_ASSERT_TRUE(mat4_equals(&a, &b));
}

static void test_matrix_inequality(void)
{
    Mat4 a = {{
        { 2, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 8, 7, 6 },
        { 5, 4, 3, 2 },
    }};
    Mat4 b = {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 8, 7, 6 },
        { 5, 4, 3, 2 },
    }};

    TEST_ASSERT_FALSE(mat4_equals(&a, &b));
}

static void test_matrix4_multiplication(void)
{
    Mat4 a = {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 8, 7, 6 },
        { 5, 4, 3, 2 },
    }};
    Mat4 b = {{
        { -2, 1, 2, 3 },
        { 3, 2, 1, -1 },
        { 4, 3, 6, 5 },
        { 1, 2, 7, 8 },
    }};
    Mat4 exp = {{
        { 20, 22, 50, 48 },
        { 44, 54, 114, 108 },
        { 40, 58, 110, 102 },
        { 16, 26, 46, 42 },
    }};
    Mat4 res = mat4_mul(&a, &b);
    TEST_ASSERT_TRUE(mat4_equals(&exp, &res));
}

static void test_matrix4_vector_multiplication(void)
{
    Mat4 m = {{
        { 1, 2, 3, 4 },
        { 2, 4, 4, 2 },
        { 8, 6, 4, 1 },
        { 0, 0, 0, 1 },
    }};
    Vec4 v = tuple(1, 2, 3, 1);
    Vec4 exp = tuple(18, 24, 33, 1);
    Vec4 res = mat4_vector_mul(&m, &v);
    TEST_ASSERT_TRUE(tuple_equal(&exp, &res));
}

static void test_matrix_identity_multiplication(void)
{
    Mat4 m = {{
        { 0, 1, 2, 4 },
        { 1, 2, 4, 8 },
        { 2, 4, 8, 16 },
        { 4, 8, 16, 32 },
    }};
    Mat4 identity = IDENTITY;

    Mat4 mres = mat4_mul(&m, &identity);
    TEST_ASSERT_TRUE(mat4_equals(&m, &mres));

    Vec4 v = tuple(1, 2, 3, 4);
    Vec4 vres = mat4_vector_mul(&identity, &v);
    TEST_ASSERT_TRUE(tuple_equal(&vres, &v));
}

static void test_matrix_transpose(void)
{
    Mat4 m = {{
        { 0, 9, 3, 0 },
        { 9, 8, 0, 8 },
        { 1, 8, 5, 3 },
        { 0, 0, 5, 8 },
    }};
    Mat4 exp = {{
        { 0, 9, 1, 0 },
        { 9, 8, 8, 0 },
        { 3, 0, 5, 5 },
        { 0, 8, 3, 8 },
    }};
    Mat4 trans = mat4_transpose(&m);
    TEST_ASSERT_TRUE(mat4_equals(&exp, &trans));

    Mat4 identity = IDENTITY;
    Mat4 trans_id = mat4_transpose(&identity);
    TEST_ASSERT_TRUE(mat4_equals(&identity, &trans_id));
}

static void test_matrix2_determinant(void)
{
    Mat2 m = {{
        { 1, 5 },
        { -3, 2 },
    }};
    TEST_ASSERT_EQUAL_FLOAT(17, mat2_determinant(&m));
}

static void test_m3_submatrix(void)
{
    Mat3 m = {{
        { 1, 5, 0 },
        { -3, 2, 7 },
        { 0, 6, -3 },
    }};
    Mat2 exp = {{
        { -3, 2 },
        { 0, 6 },
    }};
    Mat2 res = mat3_submatrix(&m, 0, 2);
    TEST_ASSERT_TRUE(mat2_equals(&exp, &res));
}

static void test_m4_submatrix(void)
{
    Mat4 m = {{
        { -6, 1, 1, 6 },
        { -8, 5, 8, 6 },
        { -1, 0, 8, 2 },
        { -7, 1, -1, 1 },
    }};
    Mat3 exp = {{
        { -6, 1, 6 },
        { -8, 8, 6 },
        { -7, -1, 1 },
    }};
    Mat3 res = mat4_submatrix(&m, 2, 1);
    TEST_ASSERT_TRUE(mat3_equals(&exp, &res));
}

static void test_m3_minor(void)
{
    Mat3 m = {{
        { 3, 5, 0 },
        { 2, -1, -7 },
        { 6, -1, 5 },
    }};
    Mat2 sub = mat3_submatrix(&m, 1, 0);
    TEST_ASSERT_EQUAL_FLOAT(25, mat2_determinant(&sub));
    TEST_ASSERT_EQUAL(25, mat3_minor(&m, 1, 0));
}

static void test_m3_cofactor(void)
{
    Mat3 m = {{
        { 3, 5, 0 },
        { 2, -1, -7 },
        { 6, -1, 5 },
    }};
    TEST_ASSERT_EQUAL_FLOAT(-12, mat3_minor(&m, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(-12, mat3_cofactor(&m, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(25, mat3_minor(&m, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(-25, mat3_cofactor(&m, 1, 0));
}

static void test_m3_determinant(void)
{
    Mat3 m = {{
        { 1, 2, 6 },
        { -5, 8, -4 },
        { 2, 6, 4 },
    }};

    TEST_ASSERT_EQUAL_FLOAT(56, mat3_cofactor(&m, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(12, mat3_cofactor(&m, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(-46, mat3_cofactor(&m, 0, 2));
    TEST_ASSERT_EQUAL_FLOAT(-196, mat3_determinant(&m));
}

static void test_m4_determinant(void)
{
    Mat4 m= {{
        { -2, -8, 3, 5 },
        { -3, 1, 7, 3 },
        { 1, 2, -9, 6 },
        { -6, 7, 7, -9 },
    }};
    TEST_ASSERT_EQUAL_FLOAT(690, mat4_cofactor(&m, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(447, mat4_cofactor(&m, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(210, mat4_cofactor(&m, 0, 2));
    TEST_ASSERT_EQUAL_FLOAT(51, mat4_cofactor(&m, 0, 3));
    TEST_ASSERT_EQUAL_FLOAT(-4071, mat4_determinant(&m));
}

static void test_m4_invertible(void)
{
    Mat4 m = {{
        { 6, 4, 4, 4 },
        { 5, 5, 7, 6 },
        { 4, -9, 3, -7 },
        { 9, 1, 7, -6 },
    }};
    TEST_ASSERT_EQUAL_FLOAT(-2120, mat4_determinant(&m));
}

static void test_m4_not_invertible(void)
{
    Mat4 m = {{
        { -4, 2, -2, -3 },
        { 9, 6, 2, 6 },
        { 0, -5, 1, -5 },
        { 0, 0, 0, 0 },
    }};
    TEST_ASSERT_EQUAL_FLOAT(0, mat4_determinant(&m));
}

static void test_m4_invert1(void)
{
    Mat4 m = {{
        { -5, 2, 6, -8 },
        { 1, -5, 1, 8 },
        { 7, 7, -6, -7 },
        { 1, -3, 7, 4 },
    }};

    Mat4 exp = {{
        { 0.21805, 0.45113, 0.24060, -0.04511 },
        { -0.80827, -1.45677, -0.44361, 0.52068 },
        { -0.07895, -0.22368, -0.05263, 0.19737 },
        { -0.52256, -0.81391, -0.30075, 0.30639 },
    }};

    Mat4 inv = mat4_invert(&m);

    TEST_ASSERT_EQUAL_FLOAT(532, mat4_determinant(&m));
    TEST_ASSERT_EQUAL_FLOAT(-160, mat4_cofactor(&m, 2, 3));
    TEST_ASSERT_EQUAL_FLOAT(-160.0/532.0, inv.elem[3][2]);
    TEST_ASSERT_EQUAL_FLOAT(105, mat4_cofactor(&m, 3, 2));
    TEST_ASSERT_EQUAL_FLOAT(105.0/532.0, inv.elem[2][3]);
    TEST_ASSERT_TRUE(mat4_equals(&exp, &inv));
}

static void test_m4_invert2(void)
{
    Mat4 m = {{
        { 8, -5, 9, 2 },
        { 7, 5, 6, 1 },
        { -6, 0, 9, 6 },
        { -3, 0, -9, -4 },
    }};
    Mat4 exp = {{
        { -0.15385, -0.15385, -0.28205, -0.53846 },
        { -0.07692, 0.12308, 0.02564, 0.03077 },
        { 0.35897, 0.35897, 0.43590, 0.92308 },
        { -0.69231, -0.69231, -0.76923, -1.92308 },
    }};
    Mat4 inv = mat4_invert(&m);
    TEST_ASSERT_TRUE(mat4_equals(&exp, &inv));
}

static void test_m4_invert3(void)
{
    Mat4 m = {{
        { 9, 3, 0, 9 },
        { -5, -2, -6, -3 },
        { -4, 9, 6, 4 },
        { -7, 6, 6, 2 },
    }};
    Mat4 exp = {{
        { -0.04074, -0.07778, 0.14444, -0.22222 },
        { -0.07778, 0.03333, 0.36667, -0.33333 },
        { -0.02901, -0.14630, -0.10926, 0.12963 },
        { 0.17778, 0.06667, -0.26667, 0.33333 },
    }};
    Mat4 inv = mat4_invert(&m);
    TEST_ASSERT_TRUE(mat4_equals(&exp, &inv));
}

static void test_m4_re_invert(void)
{
    Mat4 a = {{
        { 3, -9, 7, 3 },
        { 3, -8, 2, -9 },
        { -4, 4, 4, 1 },
        { -6, 5, -1, 1 },
    }};
    Mat4 b = {{
        { 8, 2, 2, 2 },
        { 3, -1, 7, 0 },
        { 7, 0, 5, 4 },
        { 6, -2, 0, 5 },
    }};
    Mat4 a_mul_b = mat4_mul(&a, &b);
    Mat4 binv = mat4_invert(&b);
    Mat4 a_mul_b_mul_binv = mat4_mul(&a_mul_b, &binv);
    TEST_ASSERT_TRUE(mat4_equals(&a, &a_mul_b_mul_binv));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_matrix_create);
    RUN_TEST(test_matrix_equality);
    RUN_TEST(test_matrix_inequality);
    RUN_TEST(test_matrix4_multiplication);
    RUN_TEST(test_matrix4_vector_multiplication);
    RUN_TEST(test_matrix_identity_multiplication);
    RUN_TEST(test_matrix_transpose);
    RUN_TEST(test_matrix2_determinant);
    RUN_TEST(test_m3_submatrix);
    RUN_TEST(test_m4_submatrix);
    RUN_TEST(test_m3_minor);
    RUN_TEST(test_m3_cofactor);
    RUN_TEST(test_m3_determinant);
    RUN_TEST(test_m4_determinant);
    RUN_TEST(test_m4_invertible);
    RUN_TEST(test_m4_not_invertible);
    RUN_TEST(test_m4_invert1);
    RUN_TEST(test_m4_invert2);
    RUN_TEST(test_m4_invert3);
    RUN_TEST(test_m4_re_invert);
    return UNITY_END();
}
