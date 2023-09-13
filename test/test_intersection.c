#include "unity.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_aggregating_intersections(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(1, s.id);
    Intersect i2 = intersect(2, s.id);
    Intersects xs = intersects(2, i1, i2);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(s.id, intersects_get(&xs, 0)->object);
    TEST_ASSERT_EQUAL_FLOAT(s.id, intersects_get(&xs, 1)->object);
    intersects_destroy(&xs);
}

static void test_intersection_has_object(void)
{
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = intersect_sphere(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(s.id, intersects_get(&xs, 0)->object);
    TEST_ASSERT_EQUAL_FLOAT(s.id, intersects_get(&xs, 1)->object);
    intersects_destroy(&xs);
}

static void test_hit_with_all_positives(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(1, s.id);
    Intersect i2 = intersect(2, s.id);
    Intersects xs = intersects(2, i1, i2);
    Intersect *hit = intersect_hit(&xs);
    TEST_ASSERT_TRUE(intersect_equal(&i1, hit));
    intersects_destroy(&xs);
}

static void test_hit_when_some_negative(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(-1, s.id);
    Intersect i2 = intersect(1, s.id);
    Intersects xs = intersects(2, i1, i2);
    Intersect *hit = intersect_hit(&xs);
    TEST_ASSERT_TRUE(intersect_equal(&i2, hit));
    intersects_destroy(&xs);
}

static void test_hit_when_all_negative(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(-2, s.id);
    Intersect i2 = intersect(-1, s.id);
    Intersects xs = intersects(2, i1, i2);
    Intersect *hit = intersect_hit(&xs);
    TEST_ASSERT_EQUAL_PTR(NULL, hit);
    intersects_destroy(&xs);
}

static void test_hit_unordered_intersects(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(5, s.id);
    Intersect i2 = intersect(7, s.id);
    Intersect i3 = intersect(-3, s.id);
    Intersect i4 = intersect(2, s.id);
    Intersects xs = intersects(4, i1, i2, i3, i4);
    Intersect *hit = intersect_hit(&xs);
    TEST_ASSERT_EQUAL_FLOAT(2, hit->t);
    TEST_ASSERT_TRUE(intersect_equal(&i4, hit));
    intersects_destroy(&xs);
    TEST_ASSERT_EQUAL_PTR(NULL, xs.head);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_aggregating_intersections);
    RUN_TEST(test_intersection_has_object);
    RUN_TEST(test_hit_with_all_positives);
    RUN_TEST(test_hit_when_some_negative);
    RUN_TEST(test_hit_when_all_negative);
    RUN_TEST(test_hit_unordered_intersects);
    return UNITY_END();
}