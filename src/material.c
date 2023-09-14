#include <math.h>
#include "material.h"

Material material(void)
{
    return (Material) {
        .color = color(1, 1, 1),
        .ambient = 0.1,
        .diffuse = 0.9,
        .specular = 0.9,
        .shininess = 200.0,
    };
}

Color material_lighting(const Material *m,
                        const PointLight *light,
                        const Point *point,
                        const Vec4 *eyev,
                        const Vec4 *normal)
{
    Color effective_color = tuple_prod(&m->color, &light->intensity);
    Vec4 lightv = tuple_sub(&light->position, point);
    lightv = tuple_normalize(&lightv);
    Color ambient = tuple_mul(&effective_color, m->ambient);
    f32 light_dot_normal = tuple_dot(&lightv, normal);

    Color diffuse = BLACK;
    Color specular = BLACK;
    if (light_dot_normal > 0) {
        diffuse = tuple_mul(&effective_color, m->diffuse * light_dot_normal);
        Vec4 neg_lightv = tuple_neg(&lightv);
        Vec4 reflectv = tuple_reflect(&neg_lightv, normal);
        f32 reflect_dot_eye = tuple_dot(&reflectv, eyev);

        if (reflect_dot_eye > 0) {
            f32 factor = pow(reflect_dot_eye, m->shininess);
            specular = tuple_mul(&light->intensity, m->specular * factor);
        }
    }

    Color result = ambient;
    result = tuple_add(&result, &diffuse);
    return tuple_add(&result, &specular);
}
