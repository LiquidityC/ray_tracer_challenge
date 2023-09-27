#ifndef TEST_MACROS_H_
#define TEST_MACROS_H_

#include "unity.h"
#include "float.h"

static float epsilon = EPSILON;

#define TEST_ASSERT_EQUAL_VEC4(a, b) \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, a.x, b.x); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, a.y, b.y); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, a.z, b.z); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, a.w, b.w)

#define TEST_ASSERT_EQUAL_COLOR(e, c) \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, e.r, c.r); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, e.g, c.g); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, e.b, c.b)

#define TEST_ASSERT_EQUAL_MATERIAL(e, m) \
    TEST_ASSERT_EQUAL_VEC4(e.color, m.color); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, e.ambient, m.ambient); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, e.diffuse, m.diffuse); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, e.specular, m.specular); \
    TEST_ASSERT_DOUBLE_WITHIN(epsilon, e.shininess, m.shininess)

#define TEST_ASSERT_EQUAL_MAT4(a, b) \
    TEST_ASSERT_EQUAL_VEC4(a.rows[0], b.rows[0]); \
    TEST_ASSERT_EQUAL_VEC4(a.rows[1], b.rows[1]); \
    TEST_ASSERT_EQUAL_VEC4(a.rows[2], b.rows[2]); \
    TEST_ASSERT_EQUAL_VEC4(a.rows[3], b.rows[3])

#define TEST_ASSERT_EQUAL_SPHERE(a, b) \
    TEST_ASSERT_EQUAL_MATERIAL(a.material, b.material); \
    TEST_ASSERT_EQUAL_MAT4(a.transform, b.transform)

#define TEST_ASSERT_EQUAL_POINTLIGHT(l1, l2) \
    TEST_ASSERT_EQUAL_VEC4(l1.position, l2.position); \
    TEST_ASSERT_EQUAL_COLOR(l1.intensity, l2.intensity)

#endif  // TEST_MACROS_H_

