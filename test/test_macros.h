#ifndef TEST_MACROS_H_
#define TEST_MACROS_H_

#include "unity.h"

#define TEST_ASSERT_EQUAL_VEC4(a, b) \
    TEST_ASSERT_EQUAL_FLOAT(a.x, b.x); \
    TEST_ASSERT_EQUAL_FLOAT(a.y, b.y); \
    TEST_ASSERT_EQUAL_FLOAT(a.z, b.z); \
    TEST_ASSERT_EQUAL_FLOAT(a.w, b.w)

#define TEST_ASSERT_EQUAL_COLOR(e, c) \
    TEST_ASSERT_EQUAL_FLOAT(e.r, c.r); \
    TEST_ASSERT_EQUAL_FLOAT(e.g, c.g); \
    TEST_ASSERT_EQUAL_FLOAT(e.b, c.b)

#define TEST_ASSERT_EQUAL_MATERIAL(e, m) \
    TEST_ASSERT_EQUAL_VEC4(e.color, m.color); \
    TEST_ASSERT_EQUAL_FLOAT(e.ambient, m.ambient); \
    TEST_ASSERT_EQUAL_FLOAT(e.diffuse, m.diffuse); \
    TEST_ASSERT_EQUAL_FLOAT(e.specular, m.specular); \
    TEST_ASSERT_EQUAL_FLOAT(e.shininess, m.shininess)

#endif  // TEST_MACROS_H_

