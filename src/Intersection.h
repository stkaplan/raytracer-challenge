#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "common.h"

#include <optional>
#include <ostream>
#include <vector>

namespace raytracer {

class Sphere;

class Intersection {
private:
    double t; // Distance of intersection
    const Sphere& object;

public:
    Intersection(double t, const Sphere& object)
        : t(t), object(object)
    { }

    double get_t() const { return t; }
    const auto& get_object() const { return object; }

    bool operator==(const Intersection& other) const {
        return float_equals(t, other.t)
            && &object == &other.object;
    }

    friend std::ostream& operator<<(std::ostream& os, const Intersection& i) {
        return os << "Intersection(" << i.t << ", " << &i.object << ")\n";
    }
};

// Returns intersection with smallest non-negative t.
std::optional<Intersection> find_hit(const std::vector<Intersection>& intersections);

} // namespace raytracer

#endif // _INTERSECTION_H_
