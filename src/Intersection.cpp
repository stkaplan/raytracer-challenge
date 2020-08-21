#include "Intersection.h"

#include "Ray.h"
#include "Sphere.h"

#include <optional>
#include <vector>

namespace raytracer {

HitComputation Intersection::prepare_hit_computation(const Ray& ray) {
    auto point = ray.position(t);
    auto eye_vector = -ray.get_direction();
    auto normal_vector = object->normal_at(point);
    bool inside = normal_vector.dot_product(eye_vector) < 0;
    if (inside) normal_vector = -normal_vector;
    return HitComputation(*this, point, eye_vector, normal_vector, inside);
}

std::optional<Intersection> find_hit(const std::vector<Intersection>& intersections) {
    Intersection const * best = nullptr;
    for (const auto& intersection : intersections) {
        double t = intersection.get_t();
        if (t >= 0.0) {
            if (!best || t < best->get_t()) {
                best = &intersection;
            }
        }
    }
    return best ? std::optional<Intersection>(*best) : std::nullopt;
}

} // namespace raytracer
