#include <math.h>
#include "float.h"
#include "unity.h"
#include "camera.h"
#include "test_macros.h"
#include "utils.h"

void setUp() { }

void tearDown() { }

static void test_camera_construction(void)
{
    f64 hsize = 160;
    f64 vsize = 120;
    f64 fov = M_PI/2;
    Camera c = camera(hsize, vsize, fov);
    TEST_ASSERT_EQUAL_DOUBLE(160, c.hsize);
    TEST_ASSERT_EQUAL_DOUBLE(120, c.vsize);
    TEST_ASSERT_EQUAL_DOUBLE(M_PI/2, c.fov);
    TEST_ASSERT_EQUAL_MAT4(IDENTITY, c.transform);
}

static void test_camera_pixel_size(void)
{
    f64 hsize = 160;
    f64 vsize = 120;
    f64 fov = M_PI/2;
    Camera c = camera(hsize, vsize, fov);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.01, c.pixel_size);
}

static void test_camera_center_canvas_ray(void)
{
    Camera c = camera(201, 101, M_PI/2);
    Ray r = camera_ray_for_pixel(&c, 100, 50);
    TEST_ASSERT_EQUAL_VEC4(point(0, 0, 0), r.origin);
    TEST_ASSERT_EQUAL_VEC4(vector(0, 0, -1), r.direction);
}

static void test_camera_corner_canvas_ray(void)
{
    Camera c = camera(201, 101, M_PI/2);
    Ray r = camera_ray_for_pixel(&c, 0, 0);
    TEST_ASSERT_EQUAL_VEC4(point(0, 0, 0), r.origin);
    TEST_ASSERT_EQUAL_VEC4(vector(0.66519, 0.33259, -0.66851), r.direction);
}

static void test_camera_transformed_camera_ray(void)
{
    Camera c = camera(201, 101, M_PI/2);
    c.transform = rotation_y(M_PI/4);
    c.transform = mat4_mul(&c.transform, &translation(0, -2, 5));
    Ray r = camera_ray_for_pixel(&c, 100, 50);
    TEST_ASSERT_EQUAL_VEC4(point(0, 2, -5), r.origin);
    TEST_ASSERT_EQUAL_VEC4(vector(sqrt(2)/2, 0, -sqrt(2)/2), r.direction);
}

static void test_camera_render_world(void)
{
    World w = default_world();
    Camera c = camera(11, 11, M_PI/2);
    Point from = point(0, 0, -5);
    Point to = point(0, 0, 0);
    Vec4 up = vector(0, 1, 0);
    c.transform = mat4_view_transform(&from, &to, &up);

    Canvas image = camera_render(&c, &w);
    Color col = *canvas_get_pixel(&image, 5, 5);
    TEST_ASSERT_EQUAL_COLOR(color(0.38066, 0.47583, 0.2855), col);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_camera_construction);
    RUN_TEST(test_camera_pixel_size);
    RUN_TEST(test_camera_center_canvas_ray);
    RUN_TEST(test_camera_corner_canvas_ray);
    RUN_TEST(test_camera_transformed_camera_ray);
    RUN_TEST(test_camera_render_world);
    return UNITY_END();
}
