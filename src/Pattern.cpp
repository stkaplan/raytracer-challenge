#include "Pattern.h"

#include "Color.h"
#include "Shape.h"

namespace raytracer {

Color Pattern::color_at_object(const Shape& object, const Tuple4& world_point) const {
    auto object_point = object.get_transform_inverse() * world_point;
    auto pattern_point = get_transform_inverse() * object_point;
    return color_at(pattern_point);
}

} // namespace raytracer
