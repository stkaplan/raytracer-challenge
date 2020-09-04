#ifndef _PLANE_H_
#define _PLANE_H_

#include "Intersection.h"
#include "Shape.h"
#include "Tuple.h"

#include <vector>

namespace raytracer {

class Ray;

class Plane final : public Shape {
public:
    Plane() : Shape() { }
    std::vector<Intersection> local_intersect(const Ray& ray) const override;
    Tuple4 local_normal_at(const Tuple4& point) const override;
};

} // namespace raytracer

#endif // _PLANE_H_
