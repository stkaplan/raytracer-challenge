#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <vector>

namespace raytracer {

class Ray;

class Sphere {
public:
    std::vector<double> intersect(const Ray& ray);
};

} // namespace raytracer

#endif // _SPHERE_H_
