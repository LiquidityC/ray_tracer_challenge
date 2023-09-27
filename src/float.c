#include <float.h>
#include <math.h>

bool fequal(f32 a, f32 b)
{
    return fabs(a-b) < EPSILON;
}

bool dequal(f64 a, f64 b)
{
    return fabs(a-b) < EPSILON;
}
