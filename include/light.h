#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "tuple.h"

typedef struct PointLight {
    Point position;
    Color intensity;
} PointLight;

#define point_light(position, intensity) ((PointLight) { position, intensity })

#endif  // _LIGHT_H_

