#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "common.h"
#include "Tuple.h"

#include <optional>
#include <ostream>
#include <vector>

namespace raytracer {

class HitComputation;
class Ray;
class Sphere;

class Intersection {
private:
    double t; // Distance of intersection
    const Sphere* object; // Non-owning pointer

public:
    Intersection(double t, const Sphere& object)
        : t(t), object(&object)
    { }

    Intersection(const Intersection&) = default;
    Intersection(Intersection&&) = default;
    Intersection& operator=(const Intersection& other) = default;

    double get_t() const { return t; }
    const Sphere& get_object() const { return *object; }

    bool operator==(const Intersection& other) const {
        return float_equals(t, other.t)
            && object == other.object;
    }

    friend std::ostream& operator<<(std::ostream& os, const Intersection& i) {
        return os << "Intersection(" << i.t << ", " << i.object << ")";
    }

    HitComputation prepare_hit_computation(const Ray& ray);
};

class HitComputation {
    private:
        Intersection intersection;
        Tuple4 point;
        Tuple4 eye_vector;
        Tuple4 normal_vector;
        bool inside;

    public:
        HitComputation(const Intersection& intersection, Tuple4 point,
                       Tuple4 eye_vector, Tuple4 normal_vector, bool inside)
            : intersection(intersection), point(point),
              eye_vector(eye_vector), normal_vector(normal_vector),
              inside(inside)
        { }

        const Intersection& get_intersection() const { return intersection; }
        const Tuple4& get_point() const { return point; }
        const Tuple4& get_eye_vector() const { return eye_vector; }
        const Tuple4& get_normal_vector() const { return normal_vector; }
        bool is_inside() const { return inside; }
};

// Returns intersection with smallest non-negative t.
std::optional<Intersection> find_hit(const std::vector<Intersection>& intersections);

} // namespace raytracer

#endif // _INTERSECTION_H_
