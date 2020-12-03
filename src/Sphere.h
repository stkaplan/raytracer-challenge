#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Intersection.h"
#include "Shape.h"
#include "Tuple.h"

#include <vector>

namespace raytracer {

class Ray;

class Sphere final : public Shape {
public:
    Sphere() : Shape() { }
    std::vector<Intersection> local_intersect(const Ray& ray) const override;
    Tuple4 local_normal_at(const Tuple4& point) const override;

    static Sphere glass_sphere() {
        Sphere s;
        s.get_material().set_transparency(1.0);
        s.get_material().set_refractive_index(1.5);
        return s;
    }
};

} // namespace raytracer

#endif // _SPHERE_H_
