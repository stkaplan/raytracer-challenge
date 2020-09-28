#include "World.h"

#include "Color.h"
#include "Intersection.h"
#include "Ray.h"
#include "Sphere.h"
#include "Tuple.h"

#include <cassert>
#include <memory>

namespace raytracer {

World World::default_world() {
    World w;
    w.set_light({make_point(-10, 10, -10), make_color(1, 1, 1)});

    auto s1 = std::make_unique<Sphere>();
    Material m1;
    m1.set_color(make_color(0.8, 1.0, 0.6));
    m1.set_diffuse(0.7);
    m1.set_specular(0.2);
    s1->set_material(m1);
    w.add_object(std::move(s1));

    auto s2 = std::make_unique<Sphere>();
    s2->set_transform(scale(0.5, 0.5, 0.5));
    w.add_object(std::move(s2));

    return w;
}

std::vector<Intersection> World::intersect(const Ray& ray) const {
    std::vector<Intersection> intersections;

    for (const auto& object : objects) {
        auto object_intersections = object->intersect(ray);
        std::copy(object_intersections.begin(), object_intersections.end(),
                  std::back_inserter(intersections));
    }

    std::sort(intersections.begin(), intersections.end(),
        [](const auto& a, const auto& b) {
            return a.get_t() < b.get_t();
        });
    return intersections;
}

Color World::shade_hit(const HitComputation& comp) const {
    const Material& material = comp.get_intersection().get_object().get_material();
    assert(light.has_value()); // TODO: What happens if there's no light?
    return material.lighting(comp.get_intersection().get_object(),
            *light, comp.get_point(), comp.get_eye_vector(),
            comp.get_normal_vector(), is_shadowed(comp.get_over_point()));
}

Color World::color_at(const Ray& r) const {
    auto intersections = intersect(r);
    auto hit = find_hit(intersections);
    if (!hit) return Color(0, 0, 0);

    auto comp = hit->prepare_hit_computation(r);
    return shade_hit(comp);
}

bool World::is_shadowed(const Tuple4& point) const {
    if (!light.has_value()) return false;

    auto vector = light->get_position() - point;
    Ray ray(point, vector.normalize());

    auto hit = find_hit(intersect(ray));
    return hit && hit->get_t() < vector.magnitude();
}
} // namespace raytracer
