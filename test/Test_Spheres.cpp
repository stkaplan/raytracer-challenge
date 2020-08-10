#include "catch.hpp"
#include "Sphere.h"

#include "Ray.h"
#include "Transformations.h"

using namespace raytracer;

TEST_CASE("Sphere has default transformation of identity matrix")
{
    Sphere s;
    REQUIRE(s.get_transform() == make_identity<double, 4>());
}

TEST_CASE("Can set transformation for sphere")
{
    auto t = translation(2, 3, 4);
    Sphere s(t);
    REQUIRE(s.get_transform() == t);
}

TEST_CASE("Ray intersection with scaled sphere")
{
    auto origin = make_point(0, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s(scale(2, 2, 2));

    auto result = s.intersect(r);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].get_t() == 3);
    REQUIRE(result[1].get_t() == 7);
}

TEST_CASE("Ray intersection with translated sphere")
{
    auto origin = make_point(0, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s(translation(5, 0, 0));

    auto result = s.intersect(r);
    REQUIRE(result.size() == 0);
}
