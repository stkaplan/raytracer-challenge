#ifndef _WORLD_H_
#define _WORLD_H_

#include "Color.h"
#include "Intersection.h"
#include "PointLight.h"
#include "Shape.h"

#include <algorithm>
#include <memory>
#include <optional>
#include <vector>

namespace raytracer {

class Ray;

class World {
private:
    std::optional<PointLight> light;
    std::vector<std::unique_ptr<Shape>> objects;

    static constexpr int MAX_RECURSION_DEPTH = 5;

public:
    World() { }
    static World default_world();

    const std::optional<PointLight>& get_light() const { return light; }
    void set_light(const PointLight& l) { light = l; }

    auto num_objects() const { return objects.size(); }
    auto& get_object(size_t i) { return *objects[i]; }
    const auto& get_object(size_t i) const { return *objects[i]; }
    auto begin_objects() const { return objects.begin(); }
    auto end_objects() const { return objects.end(); }
    void add_object(std::unique_ptr<Shape> s) { objects.push_back(std::move(s)); }

    std::vector<Intersection> intersect(const Ray& ray) const;
    Color shade_hit(const HitComputation& comp, int remaining = MAX_RECURSION_DEPTH) const;
    Color color_at(const Ray& r, int remaining = MAX_RECURSION_DEPTH) const;
    bool is_shadowed(const Tuple4& point) const;
    Color reflected_color(const HitComputation& comp, int remaining = MAX_RECURSION_DEPTH) const;
    Color refracted_color(const HitComputation& comp, int remaining = MAX_RECURSION_DEPTH) const;
};

} // namespace raytracer

#endif // _WORLD_H_
