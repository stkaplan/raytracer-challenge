#include "catch.hpp"
#include "Plane.h"

#include "Ray.h"

using namespace raytracer;

TEST_CASE("Normal of plane is constant everywhere")
{
    Plane p;

    auto n1 = p.local_normal_at(make_point(0, 0, 0));
    auto n2 = p.local_normal_at(make_point(10, 0, -10));
    auto n3 = p.local_normal_at(make_point(-5, 0, 150));

    REQUIRE(n1 == make_vector(0, 1, 0));
    REQUIRE(n2 == make_vector(0, 1, 0));
    REQUIRE(n3 == make_vector(0, 1, 0));
}

TEST_CASE("Intersect with ray parallel to plane")
{
    Plane p;
    Ray r(make_point(0, 10, 0), make_vector(0, 0, 1));
    auto result = p.intersect(r);
    REQUIRE(result.size() == 0);
}

TEST_CASE("Intersect with coplanar ray")
{
    Plane p;
    Ray r(make_point(0, 0, 0), make_vector(0, 0, 1));
    auto result = p.intersect(r);
    REQUIRE(result.size() == 0);
}

TEST_CASE("Ray intersecting plane from above")
{
    Plane p;
    Ray r(make_point(0, 1, 0), make_vector(0, -1, 0));
    auto result = p.intersect(r);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == Intersection(1, p));
}

TEST_CASE("Ray intersecting plane from below")
{
    Plane p;
    Ray r(make_point(0, -1, 0), make_vector(0, 1, 0));
    auto result = p.intersect(r);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == Intersection(1, p));
}
