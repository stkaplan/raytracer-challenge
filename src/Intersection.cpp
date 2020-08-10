#include "Intersection.h"

#include <optional>
#include <vector>

namespace raytracer {

std::optional<Intersection> find_hit(const std::vector<Intersection>& intersections) {
    Intersection const * best = nullptr;
    for (const auto& intersection : intersections) {
        double t = intersection.get_t();
        if (t >= 0.0) {
            if (best && t < best->get_t()) {
                best = &intersection;
            } else {
                best = &intersection;
            }
        }
    }
    return best ? std::optional<Intersection>(*best) : std::nullopt;
}

} // namespace raytracer
