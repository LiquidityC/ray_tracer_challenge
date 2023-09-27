#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <stdbool.h>

#include "tuple.h"
#include "common.h"
#include "light.h"

typedef struct Material {
    Color color;
    f64 ambient;
    f64 diffuse;
    f64 specular;
    f64 shininess;
} Material;

Material material(void);

Color material_lighting(
        const Material *m,
        const PointLight *light,
        const Point *position,
        const Vec4 *eyev,
        const Vec4 *normal,
        bool in_shadow);

#endif  // _MATERIAL_H_

