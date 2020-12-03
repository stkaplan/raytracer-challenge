#include "Intersection.h"

#include "Ray.h"
#include "Shape.h"

#include <optional>
#include <vector>

namespace raytracer {

HitComputation Intersection::prepare_hit_computation(const Ray& ray) const {
    return prepare_hit_computation(ray, {*this});
}

HitComputation Intersection::prepare_hit_computation(const Ray& ray,
        const std::vector<Intersection>& xs) const {
    auto point = ray.position(t);
    auto eye_vector = -ray.get_direction();
    auto normal_vector = object->normal_at(point);
    bool inside = normal_vector.dot_product(eye_vector) < 0;
    if (inside) normal_vector = -normal_vector;
    auto reflect_vector = ray.get_direction().reflect(normal_vector);

    std::vector<const Shape*> containers;
    double n1 = 1.0;
    double n2 = 1.0;
    for (const auto& i : xs) {
        if (i == *this) {
            n1 = containers.empty() ? 1.0 : containers.back()->get_material().get_refractive_index();
        }

        if (auto it = std::find(containers.begin(), containers.end(), &i.get_object()); it != containers.end()) {
            containers.erase(it);
        } else {
            containers.push_back(&i.get_object());
        }

        if (i == *this) {
            n2 = containers.empty() ? 1.0 : containers.back()->get_material().get_refractive_index();
        }
    }

    return HitComputation(*this, point, eye_vector, normal_vector, reflect_vector, n1, n2, inside);
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
