#ifndef _COMMON_H_
#define _COMMON_H_

#include <cmath>

namespace raytracer {

static constexpr double EPSILON = 1e-5;

template<typename T>
static constexpr bool float_equals(T x, T y)
{
    return std::fabs(x - y) < EPSILON;
}

} // namespace raytracer

#endif // _COMMON_H_