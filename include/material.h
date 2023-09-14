#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "tuple.h"
#include "common.h"
#include "light.h"

typedef struct Material {
    Color color;
    f32 ambient;
    f32 diffuse;
    f32 specular;
    f32 shininess;
} Material;

Material material(void);

Color material_lighting(
        const Material *m,
        const PointLight *light,
        const Point *position,
        const Vec4 *eyev,
        const Vec4 *normal);

#endif  // _MATERIAL_H_

