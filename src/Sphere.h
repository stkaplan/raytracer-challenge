#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Intersection.h"
#include "Matrix.h"
#include "Transformations.h"

#include <vector>

namespace raytracer {

class Ray;

class Sphere {
private:
    TransformationMatrix transform;
public:
    Sphere()
        : transform(make_identity<double, 4>())
    { }
    Sphere(const TransformationMatrix& transform)
        : transform(transform)
    { }

    const TransformationMatrix& get_transform() const { return transform; }
    void set_transform(const TransformationMatrix& m) { transform = m; }

    std::vector<Intersection> intersect(const Ray& ray);
};

} // namespace raytracer

#endif // _SPHERE_H_
