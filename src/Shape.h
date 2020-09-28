#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Intersection.h"
#include "Material.h"
#include "Transformations.h"

#include <vector>

namespace raytracer {

class Ray;

class Shape {
protected:
    TransformationMatrix transform;
    TransformationMatrix transform_inverse;
    TransformationMatrix transform_inverse_transpose;
    Material material;

public:
    Shape() {
        set_transform(make_identity<double, 4>());
    }

    bool operator==(const Shape& other) const {
        return transform == other.transform && material == other.material;
    }

    const TransformationMatrix& get_transform() const { return transform; }
    void set_transform(const TransformationMatrix& m) {
        transform = m;
        transform_inverse = transform.inverse().value();
        transform_inverse_transpose = transform_inverse.transpose();
    }

    const TransformationMatrix& get_transform_inverse() const { return transform_inverse; }

    Material& get_material() { return material; }
    const Material& get_material() const { return material; }
    void set_material(const Material& m) { material = m; }

    std::vector<Intersection> intersect(const Ray& ray) const;
    virtual std::vector<Intersection> local_intersect(const Ray& ray) const = 0;

    Tuple4 normal_at(const Tuple4& world_point) const;
    virtual Tuple4 local_normal_at(const Tuple4& world_point) const = 0;
};

} // namespace raytracer

#endif // _SHAPE_H_
