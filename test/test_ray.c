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

static void test_ray(void)
{
    Point origin = point(1, 2, 3);
    Vec4 direction = vector(4, 5, 6);
    Ray ray = ray(origin, direction);

    TEST_ASSERT_TRUE(vec4_equal(&origin, &ray.origin));
    TEST_ASSERT_TRUE(vec4_equal(&direction, &ray.direction));
}

static void test_ray_point_from_distance(void)
{
    Ray r = ray(point(2, 3, 4), vector(1, 0, 0));

    Point p1 = ray_position(&r, 0);
    Point e1 = point(2, 3, 4);
    TEST_ASSERT_TRUE(vec4_equal(&e1, &p1));

    Point p2 = ray_position(&r, 1);
    Point e2 = point(3, 3, 4);
    TEST_ASSERT_TRUE(vec4_equal(&e2, &p2));

    Point p3 = ray_position(&r, -1);
    Point e3 = point(1, 3, 4);
    TEST_ASSERT_TRUE(vec4_equal(&e3, &p3));

    Point p4 = ray_position(&r, 2.5);
    Point e4 = point(4.5, 3, 4);
    TEST_ASSERT_TRUE(vec4_equal(&e4, &p4));
}

static void test_ray_sphere_intersection(void)
{
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = sphere_intersect(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(4, xs.xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(6, xs.xs[1].t);
    intersects_destroy(&xs);
}

static void test_ray_sphere_glance(void)
{
    Ray r = ray(point(0, 1, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = sphere_intersect(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(5, xs.xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(5, xs.xs[1].t);
    intersects_destroy(&xs);
}

static void test_ray_sphere_miss(void)
{
    Ray r = ray(point(0, 2, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = sphere_intersect(&s, &r);
    TEST_ASSERT_EQUAL_size_t(0, xs.len);
    intersects_destroy(&xs);
}

static void test_ray_sphere_inside(void)
{
    Ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = sphere_intersect(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(-1, xs.xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(1, xs.xs[1].t);
    intersects_destroy(&xs);
}

static void test_ray_sphere_behind(void)
{
    Ray r = ray(point(0, 0, 5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = sphere_intersect(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(-6, xs.xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(-4, xs.xs[1].t);
    intersects_destroy(&xs);
}

static void test_aggregating_intersections(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(1, s);
    Intersect i2 = intersect(2, s);
    Intersects xs = intersects(2, i1, i2);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(s, xs.xs[0].object);
    TEST_ASSERT_EQUAL_FLOAT(s, xs.xs[1].object);
    intersects_destroy(&xs);
}

static void test_intersection_has_object(void)
{
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersects xs = sphere_intersect(&s, &r);
    TEST_ASSERT_EQUAL_size_t(2, xs.len);
    TEST_ASSERT_EQUAL_FLOAT(s, xs.xs[0].object);
    TEST_ASSERT_EQUAL_FLOAT(s, xs.xs[1].object);
    intersects_destroy(&xs);
}

static void test_hit_with_all_positives(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(1, s);
    Intersect i2 = intersect(2, s);
    Intersects xs = intersects(2, i1, i2);
    Intersect *hit = intersect_hit(&xs);
    TEST_ASSERT_TRUE(intersect_equal(&i1, hit));
    intersects_destroy(&xs);
}

static void test_hit_when_some_negative(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(-1, s);
    Intersect i2 = intersect(1, s);
    Intersects xs = intersects(2, i1, i2);
    Intersect *hit = intersect_hit(&xs);
    TEST_ASSERT_TRUE(intersect_equal(&i2, hit));
    intersects_destroy(&xs);
}

static void test_hit_when_all_negative(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(-2, s);
    Intersect i2 = intersect(-1, s);
    Intersects xs = intersects(2, i1, i2);
    Intersect *hit = intersect_hit(&xs);
    TEST_ASSERT_EQUAL_PTR(NULL, hit);
    intersects_destroy(&xs);
}

static void test_hit_unordered_intersects(void)
{
    Sphere s = sphere();
    Intersect i1 = intersect(5, s);
    Intersect i2 = intersect(7, s);
    Intersect i3 = intersect(-3, s);
    Intersect i4 = intersect(2, s);
    Intersects xs = intersects(4, i1, i2, i3, i4);
    Intersect *hit = intersect_hit(&xs);
    TEST_ASSERT_EQUAL_FLOAT(2, hit->t);
    TEST_ASSERT_TRUE(intersect_equal(&i4, hit));
    intersects_destroy(&xs);
    TEST_ASSERT_EQUAL_PTR(NULL, xs.xs);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ray);
    RUN_TEST(test_ray_point_from_distance);
    RUN_TEST(test_ray_sphere_intersection);
    RUN_TEST(test_ray_sphere_glance);
    RUN_TEST(test_ray_sphere_miss);
    RUN_TEST(test_ray_sphere_inside);
    RUN_TEST(test_ray_sphere_behind);
    RUN_TEST(test_aggregating_intersections);
    RUN_TEST(test_intersection_has_object);
    RUN_TEST(test_hit_with_all_positives);
    RUN_TEST(test_hit_when_some_negative);
    RUN_TEST(test_hit_when_all_negative);
    RUN_TEST(test_hit_unordered_intersects);
    return UNITY_END();
}
