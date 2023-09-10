#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>

typedef float       f32;
typedef double      f64;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef int32_t     i32;

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
#define clamp(a, _min, _max) max(_min, min(a, _max))

#endif // _COMMON_H_

