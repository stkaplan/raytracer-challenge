#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Intersection.h"
#include "Material.h"
#include "Transformations.h"

#include <vector>

namespace raytracer {

class Ray;

class Sphere {
private:
    TransformationMatrix transform;
    Material material;

public:
    Sphere()
        : transform(make_identity<double, 4>())
    { }
    Sphere(const TransformationMatrix& transform)
        : transform(transform)
    { }

    const TransformationMatrix& get_transform() const { return transform; }
    void set_transform(const TransformationMatrix& m) { transform = m; }

    const Material& get_material() const { return material; }
    void set_material(const Material& m) { material = m; }

    std::vector<Intersection> intersect(const Ray& ray) const;
    Tuple4 normal_at(const Tuple4& world_point) const;
};

} // namespace raytracer

#endif // _SPHERE_H_
