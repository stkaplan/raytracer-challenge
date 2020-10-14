#include "CheckerPattern.h"

#include "Color.h"
#include "Tuple.h"

#include <cmath>

namespace raytracer {

Color CheckerPattern::color_at(const Tuple4& point) const {
    auto sum = static_cast<unsigned int>(std::floor(point.x()))
             + static_cast<unsigned int>(std::floor(point.y()))
             + static_cast<unsigned int>(std::floor(point.z()));
    return sum % 2 == 0 ? color1 : color2;
}

} // namespace raytracer
