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
class Shape;

class Intersection {
private:
    double t; // Distance of intersection
    const Shape* object; // Non-owning pointer

public:
    Intersection(double t, const Shape& object)
        : t(t), object(&object)
    { }

    Intersection(const Intersection&) = default;
    Intersection(Intersection&&) = default;
    Intersection& operator=(const Intersection& other) = default;

    double get_t() const { return t; }
    const Shape& get_object() const { return *object; }

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
        Tuple4 reflect_vector;
        bool inside;

        Tuple4 over_point;
    public:
        HitComputation(const Intersection& intersection, Tuple4 point,
                       Tuple4 eye_vector, Tuple4 normal_vector,
                       Tuple4 reflect_vector, bool inside)
            : intersection(intersection), point(point),
              eye_vector(eye_vector), normal_vector(normal_vector),
              reflect_vector(reflect_vector), inside(inside)
        {
            over_point = point + normal_vector * detail::EPSILON;
        }

        const Intersection& get_intersection() const { return intersection; }
        const Tuple4& get_point() const { return point; }
        const Tuple4& get_eye_vector() const { return eye_vector; }
        const Tuple4& get_normal_vector() const { return normal_vector; }
        const Tuple4& get_reflect_vector() const { return reflect_vector; }
        const Tuple4& get_over_point() const { return over_point; }
        bool is_inside() const { return inside; }
};

// Returns intersection with smallest non-negative t.
std::optional<Intersection> find_hit(const std::vector<Intersection>& intersections);

} // namespace raytracer

#endif // _INTERSECTION_H_
