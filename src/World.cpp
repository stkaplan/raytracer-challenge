#include "World.h"

namespace raytracer {

World World::default_world() {
    World w;
    w.set_light({make_point(-10, 10, -10), make_color(1, 1, 1)});

    Sphere s1;
    Material m1;
    m1.set_color(make_color(0.8, 1.0, 0.6));
    m1.set_diffuse(0.7);
    m1.set_specular(0.2);
    s1.set_material(m1);
    w.add_object(s1);

    Sphere s2;
    s2.set_transform(scale(0.5, 0.5, 0.5));
    w.add_object(s2);

    return w;
}

std::vector<Intersection> World::intersect(const Ray& ray) const {
    std::vector<Intersection> intersections;

    for (const auto& object : objects) {
        auto object_intersections = object.intersect(ray);
        std::copy(object_intersections.begin(), object_intersections.end(),
                  std::back_inserter(intersections));
    }

    std::sort(intersections.begin(), intersections.end(),
        [](const auto& a, const auto& b) {
            return a.get_t() < b.get_t();
        });
    return intersections;
}

} // namespace raytracer
