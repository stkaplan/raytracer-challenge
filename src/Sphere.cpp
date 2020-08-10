#include "Sphere.h"

#include "Intersection.h"
#include "Ray.h"

#include <cmath>
#include <vector>

namespace raytracer {

std::vector<Intersection> Sphere::intersect(const Ray& ray) {
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

} // namespace raytracer
