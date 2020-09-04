#include "catch.hpp"
#include "Test_Shape.h"

using namespace raytracer;

TEST_CASE("Default transformation")
{
    TestShape s;
    REQUIRE(s.get_transform() == make_identity<double, 4>());
}

TEST_CASE("Assigning a transformation")
{
    TestShape s;
    s.set_transform(translation(2, 3, 4));
    REQUIRE(s.get_transform() == translation(2, 3, 4));
}

TEST_CASE("Default material")
{
    TestShape s;
    REQUIRE(s.get_material() == Material());
}

TEST_CASE("Assigning a material")
{
    TestShape s;
    Material m;
    m.set_ambient(1);
    s.set_material(m);
    REQUIRE(s.get_material() == m);
}

TEST_CASE("Ray intersection with scaled shape")
{
    auto origin = make_point(0, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    TestShape s;
    s.set_transform(scale(2, 2, 2));

    auto local_origin = make_point(0, 0, -2.5);
    auto local_direction = make_vector(0, 0, 0.5);
    Ray local_ray(local_origin, local_direction);

    [[maybe_unused]] auto result = s.intersect(r);
    REQUIRE(s.saved_ray == local_ray);
}

TEST_CASE("Ray intersection with translated shape")
{
    auto origin = make_point(0, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    TestShape s;
    s.set_transform(translation(5, 0, 0));

    auto local_origin = make_point(-5, 0, -5);
    auto local_direction = make_vector(0, 0, 1);
    Ray local_ray(local_origin, local_direction);

    [[maybe_unused]] auto result = s.intersect(r);
    REQUIRE(s.saved_ray == local_ray);
}

TEST_CASE("Normal on translated shape")
{
    TestShape s;
    s.set_transform(translation(0, 1, 0));
    auto n = s.normal_at(make_point(0, 1.70711, -0.70711));
    REQUIRE(n == make_vector(0, 0.70711, -0.70711));
}

TEST_CASE("Normal on scaled and rotated sphere")
{
    auto transform = scale(1.0, 0.5, 1.0) * rotation<Dimension::Z>(M_PI / 5.0);
    TestShape s;
    s.set_transform(transform);
    auto n = s.normal_at(make_point(0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0));
    REQUIRE(n == make_vector(0, 0.97014, -0.24254));
}
