#include "Shape.h"

#include "Intersection.h"
#include "Ray.h"

#include <cassert>
#include <cmath>
#include <vector>

namespace raytracer {

std::vector<Intersection> Shape::intersect(const Ray& r) const {
    const auto ray = r.transform(transform_inverse);
    return local_intersect(ray);
}

Tuple4 Shape::normal_at(const Tuple4& world_point) const
{
    auto local_point = transform_inverse * world_point;
    auto local_normal = local_normal_at(local_point);
    auto world_normal = transform_inverse_transpose * local_normal;
    world_normal.w() = 0;
    return world_normal.normalize();
}

} // namespace raytracer
