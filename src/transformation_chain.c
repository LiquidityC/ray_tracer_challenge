#include "transformation_chain.h"

#include <stdbool.h>
#include <stdio.h>

enum Mode {
    m_Vec,
    m_Mat,
    m_Null
};

static struct {
    enum Mode mode;
    Mat4 m;
    Vec4 v;
    bool open;
} instance = { m_Null, IDENTITY, {0}, false };

#define apply(change) \
    do { \
        if (!instance.open && instance.mode != m_Null) { \
            fprintf(stderr, "No chain opened\n"); \
            return; \
        } \
        if (instance.mode == m_Mat) { \
            instance.m = mat4_mul(&instance.m, &change); \
        } else { \
            instance.v = mat4_vector_mul(&change, &instance.v); \
        } \
    } while(0)

void chain_begin_mat4(Mat4 m)
{
    if (instance.open) {
        fprintf(stderr, "Duplicate call to chain_begin()\n");
        return;
    }
    instance.mode = m_Mat;
    instance.m = m;
    instance.open = true;
}

void chain_begin_vec4(Vec4 v)
{
    if (instance.open) {
        fprintf(stderr, "Duplicate call to chain_begin()\n");
        return;
    }
    instance.mode = m_Vec;
    instance.v = v;
    instance.open = true;
}

void trans(f32 x, f32 y, f32 z)
{
    apply(translation(x, y, z));
}

void scal(f32 x, f32 y, f32 z)
{
    apply(scaling(x, y, z));
}

void rot_x(f32 r)
{
    apply(rotation_x(r));
}

void rot_y(f32 r)
{
    apply(rotation_y(r));
}

void rot_z(f32 r)
{
    apply(rotation_z(r));
}

void shear(f32 xy, f32 xz, f32 yx, f32 yz, f32 zx, f32 zy)
{
    apply(shearing(xy, xz, yx, yz, zx, zy));
}

Mat4 chain_end_mat4(void)
{
    if (!instance.open || instance.mode != m_Mat) {
        fprintf(stderr, "Invalid call to chain_end_mat4()\n");
        return IDENTITY;
    }
    Mat4 result = instance.m;
    instance.m = IDENTITY;
    instance.v = (Vec4) {0};
    instance.mode = m_Null;
    instance.open = false;
    return result;
}

Vec4 chain_end_vec4(void)
{
    if (!instance.open || instance.mode != m_Vec) {
        fprintf(stderr, "Invalid call to chain_end_vec4()\n");
        return (Vec4) {0};
    }
    Vec4 result = instance.v;
    instance.m = IDENTITY;
    instance.v = (Vec4) {0};
    instance.mode = m_Null;
    instance.open = false;
    return result;
}
