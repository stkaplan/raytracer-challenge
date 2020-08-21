#include "catch.hpp"
#include "World.h"

#include "PointLight.h"
#include "Ray.h"

using namespace raytracer;

TEST_CASE("World with no parameters")
{
    World w;
    //REQUIRE(w.num_objects() == 0);
    REQUIRE(w.begin_objects() == w.end_objects());
    REQUIRE(!w.get_light().has_value());
}

TEST_CASE("Default world")
{
    World w = World::default_world();
    PointLight light(make_point(-10, 10, -10), make_color(1, 1, 1));
    REQUIRE(w.get_light().has_value());
    REQUIRE(*w.get_light() == light);

    Sphere s1;
    Material m1;
    m1.set_color(make_color(0.8, 1.0, 0.6));
    m1.set_diffuse(0.7);
    m1.set_specular(0.2);
    s1.set_material(m1);

    Sphere s2;
    s2.set_transform(scale(0.5, 0.5, 0.5));

    auto it = w.begin_objects();
    REQUIRE(it != w.end_objects());
    REQUIRE(*it == s1);

    ++it;
    REQUIRE(it != w.end_objects());
    REQUIRE(*it == s2);

    ++it;
    REQUIRE(it == w.end_objects());
}

TEST_CASE("Intersect world with a ray")
{
    World w = World::default_world();
    Ray r(make_point(0, 0, -5), make_vector(0, 0, 1));
    std::vector<double> expected = {4.0, 4.5, 5.5, 6.0};
    auto results = w.intersect(r);
    REQUIRE(expected.size() == results.size());
    for (size_t i = 0; i < results.size(); ++i) {
        REQUIRE(expected[i] == results[i].get_t());
    }
}
