#include "matrix.h"
#include <stdio.h>
#include <stddef.h>

Mat4 mat4_view_transform(Point *from, Point *to, Vec4 *up)
{
    Vec4 forward = tuple_sub(to, from);
    forward = tuple_normalize(&forward);
    Vec4 upn = tuple_normalize(up);
    Vec4 left = tuple_cross(&forward, &upn);
    Vec4 true_up = tuple_cross(&left, &forward);
    Mat4 orientation = (Mat4) {{
        { left.x, left.y, left.z, 0 },
        { true_up.x, true_up.y, true_up.z, 0 },
        { -forward.x, -forward.y, -forward.z, 0 },
        { 0, 0, 0, 1 },
    }};
    Mat4 transform = translation(-from->x, -from->y, -from->z);
    return mat4_mul(&orientation, &transform);
}

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

f64 mat2_determinant(const Mat2 *m)
{
    f64 a = m->elem[0][0];
    f64 b = m->elem[0][1];
    f64 c = m->elem[1][0];
    f64 d = m->elem[1][1];

    return a * d - b * c;
}

f64 mat3_minor(const Mat3 *m, u32 row, u32 col)
{
    Mat2 sub = mat3_submatrix(m, row, col);
    return mat2_determinant(&sub);
}

f64 mat4_minor(const Mat4 *m, u32 row, u32 col)
{
    Mat3 sub = mat4_submatrix(m, row, col);
    return mat3_determinant(&sub);
}

f64 mat3_cofactor(const Mat3 *m, u32 row, u32 col)
{
    f64 factor = (row + col) % 2 == 1 ? -1 : 1;
    return factor * mat3_minor(m, row, col);
}

f64 mat4_cofactor(const Mat4 *m, u32 row, u32 col)
{
    f64 factor = (row + col) % 2 == 1 ? -1 : 1;
    return factor * mat4_minor(m, row, col);
}

f64 mat3_determinant(const Mat3 *m)
{
    const Vec3 *row = &m->rows[0];

    f64 res = 0;
    for (size_t i = 0; i < 3; ++i) {
        res += row->elem[i] * mat3_cofactor(m, 0, i);
    }
    return res;
}

f64 mat4_determinant(const Mat4 *m)
{
    const Vec4 *row = &m->rows[0];

    f64 res = 0;
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
    f64 determinant = mat4_determinant(m);

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
