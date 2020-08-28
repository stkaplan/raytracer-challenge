#ifndef _WORLD_H_
#define _WORLD_H_

#include "Color.h"
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

    auto num_objects() const { return objects.size(); }
    auto& get_object(size_t i) { return objects[i]; }
    auto& get_object(size_t i) const { return objects[i]; }
    auto begin_objects() const { return objects.begin(); }
    auto end_objects() const { return objects.end(); }
    void add_object(const Sphere& s) { objects.push_back(s); }

    std::vector<Intersection> intersect(const Ray& ray) const;
    Color shade_hit(const HitComputation& comp) const;
    Color color_at(const Ray& r) const;
    bool is_shadowed(const Tuple4& point) const;
};

} // namespace raytracer

#endif // _WORLD_H_
