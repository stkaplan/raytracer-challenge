#ifndef _WORLD_H_
#define _WORLD_H_

#include "Intersection.h"
#include "PointLight.h"
#include "Sphere.h"

#include <algorithm>
#include <optional>
#include <vector>

namespace raytracer {

class Ray;

class World {
private:
    std::optional<PointLight> light;
    std::vector<Sphere> objects;

public:
    World() { }
    static World default_world();

    const std::optional<PointLight>& get_light() const { return light; }
    void set_light(const PointLight& l) { light = l; }

    auto begin_objects() const { return objects.begin(); }
    auto end_objects() const { return objects.end(); }
    void add_object(const Sphere& s) { objects.push_back(s); }

    std::vector<Intersection> intersect(const Ray& ray) const;
};

} // namespace raytracer

#endif // _WORLD_H_
