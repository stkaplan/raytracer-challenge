#ifndef _RAY_H_
#define _RAY_H_

#include "Transformations.h"
#include "Tuple.h"

#include <ostream>

namespace raytracer {

class Ray {
private:
    Tuple4 origin;
    Tuple4 direction;

public:
    Ray() : origin(make_point(0, 0, 0)), direction(make_vector(0, 0, 0)) { }
    Ray(const Tuple4& origin, const Tuple4& direction)
        : origin(origin), direction(direction) 
    { }

    const auto& get_origin() const { return origin; }
    const auto& get_direction() const { return direction; }

    Tuple4 position(double t) const {
        return origin + (direction * t);
    }

    Ray transform(const TransformationMatrix& m) const {
        return Ray(m * origin, m * direction);
    }

    bool operator==(const Ray& other) const {
        return origin == other.origin && direction == other.direction;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ray& r) {
        os << "Ray(" << r.origin << ", " << r.direction << ")";
        return os;
    }
};

} // namespace raytracer

#endif // _RAY_H_
