#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdbool.h>
#include "common.h"
#include "tuple.h"

typedef union Mat2 {
    f32 elem[2][2];
    Vec2 rows[2];
} Mat2;

typedef union Mat3 {
    f32 elem[3][3];
    Vec3 rows[3];
} Mat3;

typedef union Mat4 {
    f32 elem[4][4];
    Tuple rows[4];
} Mat4;

#define IDENTITY ((Mat4) {{ \
        { 1, 0, 0, 0 }, \
        { 0, 1, 0, 0 }, \
        { 0, 0, 1, 0 }, \
        { 0, 0, 0, 1 }, \
        }})

bool mat4_equals(const Mat4 *a, const Mat4 *b);

bool mat3_equals(const Mat3 *a, const Mat3 *b);

bool mat2_equals(const Mat2 *a, const Mat2 *b);

Mat4 mat4_mul(const Mat4 *a, const Mat4 *b);

Tuple mat4_vector_mul(const Mat4 *m, const Vec4 *v);

Mat4 mat4_transpose(const Mat4 *m);

f32 mat2_determinant(const Mat2 *m);

f32 mat3_minor(const Mat3 *m, u32 row, u32 col);

f32 mat4_minor(const Mat4 *m, u32 row, u32 col);

f32 mat3_cofactor(const Mat3 *m, u32 row, u32 col);

f32 mat4_cofactor(const Mat4 *m, u32 row, u32 col);

f32 mat3_determinant(const Mat3 *m);

f32 mat4_determinant(const Mat4 *m);

Mat2 mat3_submatrix(const Mat3 *m, u32 row, u32 col);

Mat3 mat4_submatrix(const Mat4 *m, u32 row, u32 col);

bool mat4_is_invertible(const Mat4 *m);

Mat4 mat4_invert(const Mat4 *m);

void mat4_print(const Mat4 *m);

void mat3_print(const Mat3 *m);

void mat2_print(const Mat2 *m);


#endif  // _MATRIX_H_

