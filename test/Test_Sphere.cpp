#include "catch.hpp"
#include "Sphere.h"

#include "Ray.h"
#include "Transformations.h"

using namespace raytracer;

TEST_CASE("Ray intersection with scaled sphere")
{
    auto origin = make_point(0, 0, -2.5);
    auto direction = make_vector(0, 0, 0.5);
    Ray r(origin, direction);
    Sphere s;
    s.set_transform(scale(2, 2, 2));

    auto result = s.local_intersect(r);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].get_t() == 3);
    REQUIRE(result[1].get_t() == 7);
}

TEST_CASE("Ray intersection with translated sphere")
{
    auto origin = make_point(-5, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;
    s.set_transform(translation(5, 0, 0));

    auto result = s.local_intersect(r);
    REQUIRE(result.size() == 0);
}

TEST_CASE("Normal on sphere at point on x-axis")
{
    Sphere s;
    auto n = s.local_normal_at(make_point(1, 0, 0));
    REQUIRE(n == make_vector(1, 0, 0));
    REQUIRE(n == n.normalize());
}

TEST_CASE("Normal on sphere at point on y-axis")
{
    Sphere s;
    auto n = s.local_normal_at(make_point(0, 1, 0));
    REQUIRE(n == make_vector(0, 1, 0));
    REQUIRE(n == n.normalize());
}

TEST_CASE("Normal on sphere at point on z-axis")
{
    Sphere s;
    auto n = s.local_normal_at(make_point(0, 0, 1));
    REQUIRE(n == make_vector(0, 0, 1));
    REQUIRE(n == n.normalize());
}

TEST_CASE("Normal on sphere at non-axial point")
{
    Sphere s;
    double num = std::sqrt(3.0) / 3.0;
    auto n = s.local_normal_at(make_point(num, num, num));
    REQUIRE(n == make_vector(num, num, num));
    REQUIRE(n == n.normalize());
}

TEST_CASE("Normal on translated sphere")
{
    Sphere s;
    s.set_transform(translation(0, 1, 0));
    auto n = s.local_normal_at(make_point(0, 0.70711, -0.70711));
    REQUIRE(n == make_vector(0, 0.70711, -0.70711));
}

TEST_CASE("Normal on scaled and rotated sphere")
{
    auto transform = scale(1.0, 0.5, 1.0) * rotation<Dimension::Z>(M_PI / 5.0);
    Sphere s;
    s.set_transform(transform);
    auto n = s.local_normal_at(make_point(0, 0.97014, -0.24254));
    REQUIRE(n == make_vector(0, 0.97014, -0.24254));
}
