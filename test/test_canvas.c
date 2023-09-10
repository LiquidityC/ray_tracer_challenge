#include "unity.h"
#include "canvas.h"
#include <stdlib.h>
#include <string.h>

static const Color black    = color(0, 0, 0);
static const Color red      = color(1, 0, 0);

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_canvas_dimensions(void)
{
    Canvas c = canvas(10, 20);
    TEST_ASSERT_EQUAL_UINT32(10, c.width);
    TEST_ASSERT_EQUAL_UINT32(20, c.height);


    for (size_t i = 0; i < c.width * c.height; ++i) {
        TEST_ASSERT_TRUE(tuple_equal(&black, &c.grid[i]));
    }
    canvas_destroy(&c);
}

static void test_canvas_pixel_write(void)
{
    Canvas c = canvas(10, 20);
    canvas_write_pixel(&c, 2, 3, &red);
    Color *col = canvas_get_pixel(&c, 2, 3);
    TEST_ASSERT_TRUE(tuple_equal(col, &red));
    canvas_destroy(&c);
}

static void test_canvas_ppm_write_header(void)
{
    Canvas c = canvas(5, 3);

    canvas_write_ppm(&c, "canvas.ppm");

    FILE *fp = fopen("canvas.ppm", "r");
    TEST_ASSERT_TRUE(fp != NULL);

    char *line = NULL;
    size_t len;
    size_t read;

    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("P3", line, read-1);

    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("5 3", line, read-1);

    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("255", line, read-1);

    free(line);
    fclose(fp);
    canvas_destroy(&c);
}

static void test_canvas_ppm_write_body(void)
{
    Canvas c = canvas(5, 3);

    const Color c1 = color(1.5, 0, 0);
    const Color c2 = color(0, 0.5, 0);
    const Color c3 = color(0, 0, 1);

    canvas_write_pixel(&c, 0, 0, &c1);
    canvas_write_pixel(&c, 2, 1, &c2);
    canvas_write_pixel(&c, 4, 2, &c3);

    canvas_write_ppm(&c, "canvas.ppm");

    FILE *fp = fopen("canvas.ppm", "r");
    TEST_ASSERT_TRUE(fp != NULL);

    char *line = NULL;
    size_t len;
    size_t read;

    /* Skip the header lines */
    read = getline(&line, &len, fp);
    read = getline(&line, &len, fp);
    read = getline(&line, &len, fp);

    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0", line, read-1);
    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("0 0 0 0 0 0 0 128 0 0 0 0 0 0 0", line, read-1);
    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("0 0 0 0 0 0 0 0 0 0 0 0 0 0 255", line, read-1);

    free(line);
    fclose(fp);
    canvas_destroy(&c);
}

static void test_canvas_ppm_write_body_wrap(void)
{
    Canvas c = canvas(10, 2);

    const Color color = color(1, 0.8, 0.6);

    for (size_t x = 0; x < 10; ++x) {
        for (size_t y = 0; y < 2; ++y) {
            canvas_write_pixel(&c, x, y, &color);
        }
    }
    canvas_write_ppm(&c, "canvas.ppm");

    FILE *fp = fopen("canvas.ppm", "r");
    TEST_ASSERT_TRUE(fp != NULL);

    char *line = NULL;
    size_t len;
    size_t read;

    /* Skip the header lines */
    read = getline(&line, &len, fp);
    read = getline(&line, &len, fp);
    read = getline(&line, &len, fp);

    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204", line, read-1);
    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("153 255 204 153 255 204 153 255 204 153 255 204 153", line, read-1);
    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204", line, read-1);
    read = getline(&line, &len, fp);
    TEST_ASSERT_EQUAL_STRING_LEN("153 255 204 153 255 204 153 255 204 153 255 204 153", line, read-1);

    free(line);
    fclose(fp);
    canvas_destroy(&c);
}

static void test_canvas_ppm_ends_with_newline(void)
{
    Canvas c = canvas(5, 3);

    canvas_write_ppm(&c, "canvas.ppm");

    FILE *fp = fopen("canvas.ppm", "r");
    TEST_ASSERT_TRUE(fp != NULL);

    char buffer[1024];
    size_t len = fread(buffer, sizeof(char), 1024, fp);
    fclose(fp);

    TEST_ASSERT_LESS_THAN(1024, len);
    TEST_ASSERT_EQUAL_CHAR('\n', buffer[len-1]);

    canvas_destroy(&c);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_canvas_dimensions);
    RUN_TEST(test_canvas_pixel_write);
    RUN_TEST(test_canvas_ppm_write_header);
    RUN_TEST(test_canvas_ppm_write_body);
    RUN_TEST(test_canvas_ppm_write_body_wrap);
    RUN_TEST(test_canvas_ppm_ends_with_newline);
    return UNITY_END();
}
