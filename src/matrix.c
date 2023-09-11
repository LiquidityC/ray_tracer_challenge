#include "matrix.h"
#include <stdio.h>
#include <stddef.h>

bool mat4_equals(const Mat4 *a, const Mat4 *b)
{
    for (size_t i = 0; i < 4; ++i) {
        const Tuple *ta = &a->rows[i];
        const Tuple *tb = &b->rows[i];

        if (!tuple_equal(ta, tb)) {
            return false;
        }
    }
    return true;
}

bool mat3_equals(const Mat3 *a, const Mat3 *b)
{
    for (size_t i = 0; i < 3; ++i) {
        const Vec3 *ta = &a->rows[i];
        const Vec3 *tb = &b->rows[i];

        if (!vec3_equal(ta, tb)) {
            return false;
        }
    }
    return true;
}

bool mat2_equals(const Mat2 *a, const Mat2 *b)
{
    for (size_t i = 0; i < 2; ++i) {
        const Vec2 *ta = &a->rows[i];
        const Vec2 *tb = &b->rows[i];

        if (!vec2_equal(ta, tb)) {
            return false;
        }
    }
    return true;
}

Mat4 mat4_mul(const Mat4 *a, const Mat4 *b)
{
    Mat4 res = {0};
    for (size_t r = 0; r < 4; ++r) {
        for (size_t c = 0; c < 4; ++c) {
            res.elem[r][c] =
                a->elem[r][0] * b->elem[0][c] +
                a->elem[r][1] * b->elem[1][c] +
                a->elem[r][2] * b->elem[2][c] +
                a->elem[r][3] * b->elem[3][c];
        }
    }
    return res;
}

Tuple mat4_vector_mul(const Mat4 *m, const Vec4 *v)
{
    Tuple res = {0};
    for (size_t i = 0; i < 4; ++i) {
        res.elem[i] = tuple_dot(&m->rows[i], v);
    }
    return res;
}

Mat4 mat4_transpose(const Mat4 *m)
{
    Mat4 res = {0};
    for (size_t r = 0; r < 4; ++r) {
        const Tuple *t = &m->rows[r];
        for (size_t v = 0; v < 4; ++v) {
            res.elem[v][r] = t->elem[v];
        }
    }
    return res;
}

f32 mat2_determinant(const Mat2 *m)
{
    f32 a = m->elem[0][0];
    f32 b = m->elem[0][1];
    f32 c = m->elem[1][0];
    f32 d = m->elem[1][1];

    return a * d - b * c;
}

f32 mat3_minor(const Mat3 *m, u32 row, u32 col)
{
    Mat2 sub = mat3_submatrix(m, row, col);
    return mat2_determinant(&sub);
}

f32 mat4_minor(const Mat4 *m, u32 row, u32 col)
{
    Mat3 sub = mat4_submatrix(m, row, col);
    return mat3_determinant(&sub);
}

f32 mat3_cofactor(const Mat3 *m, u32 row, u32 col)
{
    f32 factor = (row + col) % 2 == 1 ? -1 : 1;
    return factor * mat3_minor(m, row, col);
}

f32 mat4_cofactor(const Mat4 *m, u32 row, u32 col)
{
    f32 factor = (row + col) % 2 == 1 ? -1 : 1;
    return factor * mat4_minor(m, row, col);
}

f32 mat3_determinant(const Mat3 *m)
{
    const Vec3 *row = &m->rows[0];

    f32 res = 0;
    for (size_t i = 0; i < 3; ++i) {
        res += row->elem[i] * mat3_cofactor(m, 0, i);
    }
    return res;
}

f32 mat4_determinant(const Mat4 *m)
{
    const Vec4 *row = &m->rows[0];

    f32 res = 0;
    for (size_t i = 0; i < 4; ++i) {
        res += row->elem[i] * mat4_cofactor(m, 0, i);
    }
    return res;
}

Mat2 mat3_submatrix(const Mat3 *m, u32 row, u32 col)
{
    Mat2 res;
    for (size_t i = 0; i < 2; ++i) {
        size_t sr = i >= row ? i + 1 : i;
        for (size_t j = 0; j < 2; ++j) {
            size_t sc = j >= col ? j + 1 : j;
            res.elem[i][j] = m->elem[sr][sc];
        }
    }
    return res;
}

Mat3 mat4_submatrix(const Mat4 *m, u32 row, u32 col)
{
    Mat3 res;
    for (size_t i = 0; i < 3; ++i) {
        size_t sr = i >= row ? i + 1 : i;
        for (size_t j = 0; j < 3; ++j) {
            size_t sc = j >= col ? j + 1 : j;
            res.elem[i][j] = m->elem[sr][sc];
        }
    }
    return res;
}

bool mat4_is_invertible(const Mat4 *m)
{
    return mat4_determinant(m) != 0;
}

Mat4 mat4_invert(const Mat4 *m)
{
    Mat4 res = {0};
    f32 determinant = mat4_determinant(m);

    if (determinant == 0) {
        goto out;
    }

    for (size_t r = 0; r < 4; ++r) {
        for (size_t c = 0; c < 4; ++c) {
            res.elem[c][r] = mat4_cofactor(m, r, c)/determinant;
        }
    }

out:
    return res;
}

void mat4_print(const Mat4 *m)
{
    for (size_t r = 0; r < 4; ++r) {
        const Tuple *t = &m->rows[r];
        printf("%.2f %.2f %.2f %.2f\n", t->x, t->y, t->z, t->w);
    }
}

void mat3_print(const Mat3 *m)
{
    for (size_t r = 0; r < 3; ++r) {
        const Vec3 *t = &m->rows[r];
        printf("%.2f %.2f %.2f\n", t->x, t->y, t->z);
    }
}

void mat2_print(const Mat2 *m)
{
    for (size_t r = 0; r < 2; ++r) {
        const Vec2 *t = &m->rows[r];
        printf("%.2f %.2f\n", t->x, t->y);
    }
}