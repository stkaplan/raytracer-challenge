#include "Plane.h"

#include "common.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"

#include <cassert>
#include <cmath>
#include <vector>

namespace raytracer {

std::vector<Intersection> Plane::local_intersect(const Ray& ray) const {
    if (std::abs(ray.get_direction().y()) < detail::EPSILON) {
        return {};
    }

    auto t = -ray.get_origin().y() / ray.get_direction().y();
    return {Intersection(t, *this)};
}

Tuple4 Plane::local_normal_at([[maybe_unused]] const Tuple4& point) const {
    return make_vector(0, 1, 0);
}

} // namespace raytracer
