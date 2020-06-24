#ifndef _COMMON_H_
#define _COMMON_H_

#include <cmath>

namespace raytracer {

namespace detail {
static constexpr double EPSILON = 1e-4;

template <typename T>
static constexpr T fabs(T x) {
    return x >= 0 ? x : -x;
}
} // namespace detail

template <typename S, typename T>
static constexpr bool float_equals(S x, T y)
{
    return detail::fabs(x - y) < detail::EPSILON;
}

} // namespace raytracer

#endif // _COMMON_H_
