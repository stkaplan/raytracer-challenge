#include "Cube.h"

#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

namespace raytracer {

namespace {
std::pair<double, double> check_axis(double origin, double direction) {
    auto tmin_numerator = -1.0 - origin;
    auto tmax_numerator = 1.0 - origin;
    double tmin, tmax;
    if (std::abs(direction) >= detail::EPSILON) {
        tmin = tmin_numerator / direction;
        tmax = tmax_numerator / direction;
    } else {
        tmin = tmin_numerator * INFINITY;
        tmax = tmax_numerator * INFINITY;
    }

    if (tmin > tmax) {
        std::swap(tmin, tmax);
    }
    return {tmin, tmax};

}
} // end anonymous namespace

std::vector<Intersection> Cube::local_intersect(const Ray& ray) const {
    auto [xtmin, xtmax] = check_axis(ray.get_origin().x(), ray.get_direction().x());
    auto [ytmin, ytmax] = check_axis(ray.get_origin().y(), ray.get_direction().y());
    auto [ztmin, ztmax] = check_axis(ray.get_origin().z(), ray.get_direction().z());

    auto tmin = std::max({xtmin, ytmin, ztmin});
    auto tmax = std::min({xtmax, ytmax, ztmax});

    if (tmin > tmax) {
        return {};
    }

    return {{tmin, *this}, {tmax, *this}};
}

Tuple4 Cube::local_normal_at(const Tuple4& point) const {
    auto maxc = std::max({std::abs(point.x()), std::abs(point.y()), std::abs(point.z())});

    if (maxc == std::abs(point.x())) {
        return make_vector(point.x(), 0, 0);
    } else if (maxc == std::abs(point.y())) {
        return make_vector(0, point.y(), 0);
    } else {
        return make_vector(0, 0, point.z());
    }
}

} // namespace raytracer
