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
    TransformationMatrix transform_inverse;
    TransformationMatrix transform_inverse_transpose;
    Material material;

public:
    Sphere() {
        set_transform(make_identity<double, 4>());
    }

    const TransformationMatrix& get_transform() const { return transform; }
    void set_transform(const TransformationMatrix& m) {
        transform = m;
        transform_inverse = transform.inverse().value();
        transform_inverse_transpose = transform_inverse.transpose();
    }

    const Material& get_material() const { return material; }
    void set_material(const Material& m) { material = m; }

    std::vector<Intersection> intersect(const Ray& ray) const;
    Tuple4 normal_at(const Tuple4& world_point) const;
};

} // namespace raytracer

#endif // _SPHERE_H_
