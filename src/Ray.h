#ifndef _RAY_H_
#define _RAY_H_

#include "Transformations.h"
#include "Tuple.h"

namespace raytracer {

class Ray {
private:
    Tuple4 origin;
    Tuple4 direction;

public:
    Ray(const Tuple4& origin, const Tuple4& direction)
        : origin(origin), direction(direction) 
    { }

    const auto& get_origin() const { return origin; }
    const auto& get_direction() const { return direction; }

    Tuple4 position(double t) const {
        return origin + (direction * t);
    }

    Ray transform(const TransformationMatrix& m) {
        return Ray(m * origin, m * direction);
    }
};

} // namespace raytracer

#endif // _RAY_H_
