#include "StripePattern.h"

#include "Color.h"
#include "Tuple.h"

#include <cmath>

namespace raytracer {

Color StripePattern::color_at(const Tuple4& point) const {
    ssize_t floor = std::floor(point.x());
    return colors[floor % colors.size()];
}

} // namespace raytracer
