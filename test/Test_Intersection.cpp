#include "catch.hpp"
#include "Intersection.h"

#include "Sphere.h"

using namespace raytracer;

TEST_CASE("Intersection encapsulates t and object")
{
    Sphere s;
    Intersection i(3.5, s);
    REQUIRE(i.get_t() == 3.5);
    REQUIRE(&i.get_object() == &s);
}

TEST_CASE("Have a hit when all intersections have positive t")
{
    Sphere s;
    Intersection i1(1, s);
    Intersection i2(2, s);
    std::vector<Intersection> xs{i2, i1};

    auto hit_value = hit(xs);
    REQUIRE(hit_value.has_value());
    REQUIRE(hit_value.value() == i1);
}

TEST_CASE("Have a hit when some intersections have negative t")
{
    Sphere s;
    Intersection i1(-1, s);
    Intersection i2(1, s);
    std::vector<Intersection> xs{i2, i1};

    auto hit_value = hit(xs);
    REQUIRE(hit_value.has_value());
    REQUIRE(hit_value.value() == i2);
}

TEST_CASE("Have a hit when all intersections have negative t")
{
    Sphere s;
    Intersection i1(-2, s);
    Intersection i2(-1, s);
    std::vector<Intersection> xs{i2, i1};

    auto hit_value = hit(xs);
    REQUIRE(hit_value == std::nullopt);
}

TEST_CASE("Hit values is always the lowest non-negative intersection")
{
    Sphere s;
    Intersection i1(5, s);
    Intersection i2(7, s);
    Intersection i3(-3, s);
    Intersection i4(2, s);
    std::vector<Intersection> xs{i1, i2, i3, i4};

    auto hit_value = hit(xs);
    REQUIRE(hit_value.has_value());
    REQUIRE(hit_value == i4);
}
