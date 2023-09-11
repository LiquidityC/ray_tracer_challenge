#ifndef _TRANSFORMATION_CHAIN_H_
#define _TRANSFORMATION_CHAIN_H_

#include "common.h"
#include "matrix.h"

void chain_begin_mat4(Mat4 m);

void chain_begin_vec4(Vec4 m);

void trans(f32 x, f32 y, f32 z);

void scal(f32 x, f32 y, f32 z);

void rot_x(f32 r);

void rot_y(f32 r);

void rot_z(f32 r);

void shear(f32 xy, f32 xz, f32 yx, f32 yz, f32 zx, f32 zy);

Mat4 chain_end_mat4(void);

Vec4 chain_end_vec4(void);

#endif // _TRANSFORMATION_CHAIN_H_

