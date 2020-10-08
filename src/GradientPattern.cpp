#include "GradientPattern.h"

#include "Color.h"
#include "Tuple.h"

#include <cmath>

namespace raytracer {

Color GradientPattern::color_at(const Tuple4& point) const {
    auto x_distance = point.x() - std::floor(point.x());
    auto color_diff = color2 - color1;
    return color1 + (color_diff * x_distance);
}

} // namespace raytracer
