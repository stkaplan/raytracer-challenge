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

TEST_CASE("Shading an intersection")
{
    World w = World::default_world();
    Ray r(make_point(0, 0, -5), make_vector(0, 0, 1));
    const Sphere& s = w.get_object(0);
    Intersection i(4, s);
    HitComputation comp = i.prepare_hit_computation(r);
    Color c = w.shade_hit(comp);
    REQUIRE(c == make_color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("Shading an intersection from the inside")
{
    World w = World::default_world();
    PointLight light(make_point(0, 0.25, 0), make_color(1, 1, 1));
    w.set_light(light);

    Ray r(make_point(0, 0, 0), make_vector(0, 0, 1));
    const Sphere& s = w.get_object(1);
    Intersection i(0.5, s);
    HitComputation comp = i.prepare_hit_computation(r);
    Color c = w.shade_hit(comp);
    REQUIRE(c == make_color(0.90498, 0.90498, 0.90498));
}

TEST_CASE("Color when ray misses")
{
    World w = World::default_world();
    Ray r(make_point(0, 0, -5), make_vector(0, 1, 0));
    Color c = w.color_at(r);
    REQUIRE(c == make_color(0, 0, 0));
}

TEST_CASE("Color when ray hits")
{
    World w = World::default_world();
    Ray r(make_point(0, 0, -5), make_vector(0, 0, 1));
    Color c = w.color_at(r);
    REQUIRE(c == make_color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("Color with intersection behind ray")
{
    World w = World::default_world();
    Sphere& outer = w.get_object(0);
    outer.get_material().set_ambient(1);
    Sphere& inner = w.get_object(1);
    inner.get_material().set_ambient(1);
    Ray r(make_point(0, 0, 0.75), make_vector(0, 0, -1));
    Color c = w.color_at(r);
    REQUIRE(c == inner.get_material().get_color());
}

TEST_CASE("There is no shadow when nothing is collinear with point and light")
{
    World w = World::default_world();
    auto p = make_point(0, 10, 0);
    REQUIRE(!w.is_shadowed(p));
}

TEST_CASE("There is shadow when an object is between point and light")
{
    World w = World::default_world();
    auto p = make_point(10, -10, 10);
    REQUIRE(w.is_shadowed(p));
}

TEST_CASE("There is no shadow when object is behind light")
{
    World w = World::default_world();
    auto p = make_point(-20, 20, -20);
    REQUIRE(!w.is_shadowed(p));
}

TEST_CASE("There is no shadow when object is behind point")
{
    World w = World::default_world();
    auto p = make_point(-2, 2, -2);
    REQUIRE(!w.is_shadowed(p));
}
