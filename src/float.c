#include <float.h>
#include <math.h>

bool fequal(float a, float b)
{
    return fabs(a-b) < EPSILON;
}
