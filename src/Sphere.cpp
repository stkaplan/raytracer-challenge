#include "Sphere.h"

#include "Intersection.h"
#include "Ray.h"

#include <cassert>
#include <cmath>
#include <vector>

namespace raytracer {

std::vector<Intersection> Sphere::intersect(const Ray& r) const {
    const auto ray = r.transform(transform_inverse);

    const auto sphere_to_ray = ray.get_origin() - make_point(0, 0, 0);
    const auto direction = ray.get_direction();

    const auto a = direction.dot_product(direction);
    const auto b = 2 * direction.dot_product(sphere_to_ray);
    const auto c = sphere_to_ray.dot_product(sphere_to_ray) - 1;
    double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0.0) return {}; // no intersection

    const auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    const auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);
    return {Intersection(t1, *this), Intersection(t2, *this)};
}

Tuple4 Sphere::normal_at(const Tuple4& world_point) const
{
    auto object_point = transform_inverse * world_point;
    auto object_normal = object_point - make_point(0, 0, 0);
    auto world_normal = transform_inverse_transpose * object_normal;
    world_normal.w() = 0;
    return world_normal.normalize();
}

} // namespace raytracer
