#ifndef _TRANSFORMATION_CHAIN_H_
#define _TRANSFORMATION_CHAIN_H_

#include "common.h"
#include "matrix.h"

void chain_begin_mat4(Mat4 m);

void chain_begin_vec4(Vec4 m);

void trans(f64 x, f64 y, f64 z);

void scal(f64 x, f64 y, f64 z);

void rot_x(f64 r);

void rot_y(f64 r);

void rot_z(f64 r);

void shear(f64 xy, f64 xz, f64 yx, f64 yz, f64 zx, f64 zy);

Mat4 chain_end_mat4(void);

Vec4 chain_end_vec4(void);

#endif // _TRANSFORMATION_CHAIN_H_

