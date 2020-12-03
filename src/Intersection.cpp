#include "Intersection.h"

#include "Ray.h"
#include "Shape.h"

#include <optional>
#include <vector>

namespace raytracer {

double HitComputation::schlick() const {
    auto cos = eye_vector.dot_product(normal_vector);

    if (n1 > n2) {
        auto n = n1 / n2;
        auto sin2_t = std::pow(n, 2) * (1.0 - std::pow(cos, 2));
        if (sin2_t > 1.0) {
            return 1.0;
        }

        auto cos_t = std::sqrt(1.0 - sin2_t);
        cos = cos_t;
    }

    auto r0 = std::pow((n1 - n2) / (n1 + n2), 2);
    return r0 + (1.0 - r0) * std::pow(1.0 - cos, 5);
}

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
