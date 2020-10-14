#include "RingPattern.h"

#include "Color.h"
#include "Tuple.h"

#include <cmath>

namespace raytracer {

Color RingPattern::color_at(const Tuple4& point) const {
    auto dist = std::sqrt(point.x() * point.x()) + (point.z() * point.z());
    auto color = static_cast<unsigned int>(std::floor(dist)) % 2;
    return color == 0 ? color1 : color2;
}

} // namespace raytracer
