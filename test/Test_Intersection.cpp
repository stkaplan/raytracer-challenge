#include "catch.hpp"
#include "Intersection.h"

#include "Plane.h"
#include "Ray.h"
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

    auto hit = find_hit(xs);
    REQUIRE(hit.has_value());
    REQUIRE(hit.value() == i1);
}

TEST_CASE("Have a hit when some intersections have negative t")
{
    Sphere s;
    Intersection i1(-1, s);
    Intersection i2(1, s);
    std::vector<Intersection> xs{i2, i1};

    auto hit = find_hit(xs);
    REQUIRE(hit.has_value());
    REQUIRE(hit.value() == i2);
}

TEST_CASE("Have a hit when all intersections have negative t")
{
    Sphere s;
    Intersection i1(-2, s);
    Intersection i2(-1, s);
    std::vector<Intersection> xs{i2, i1};

    auto hit = find_hit(xs);
    REQUIRE(hit == std::nullopt);
}

TEST_CASE("Hit values is always the lowest non-negative intersection")
{
    Sphere s;
    Intersection i1(5, s);
    Intersection i2(7, s);
    Intersection i3(-3, s);
    Intersection i4(2, s);
    Intersection i5(3, s);
    std::vector<Intersection> xs{i1, i2, i3, i4, i5};

    auto hit = find_hit(xs);
    REQUIRE(hit.has_value());
    REQUIRE(hit == i4);
}

TEST_CASE("Pre-computing the state of an intersection")
{
    Ray r(make_point(0, 0, -5), make_vector(0, 0, 1));
    Sphere s;
    Intersection i(4, s);
    auto comps = i.prepare_hit_computation(r);
    REQUIRE(comps.get_intersection() == i);
    REQUIRE(comps.get_point() == make_point(0, 0, -1));
    REQUIRE(comps.get_eye_vector() == make_vector(0, 0, -1));
    REQUIRE(comps.get_normal_vector() == make_vector(0, 0, -1));
}

TEST_CASE("The hit, when intersection occurs on the outside")
{
    Ray r(make_point(0, 0, -5), make_vector(0, 0, 1));
    Sphere s;
    Intersection i(4, s);
    auto comps = i.prepare_hit_computation(r);
    REQUIRE(!comps.is_inside());
}

TEST_CASE("The hit, when intersection occurs on the inside")
{
    Ray r(make_point(0, 0, 0), make_vector(0, 0, 1));
    Sphere s;
    Intersection i(1, s);
    auto comps = i.prepare_hit_computation(r);
    REQUIRE(comps.get_point() == make_point(0, 0, 1));
    REQUIRE(comps.get_eye_vector() == make_vector(0, 0, -1));
    REQUIRE(comps.is_inside());
    REQUIRE(comps.get_normal_vector() == make_vector(0, 0, -1));
}

TEST_CASE("The hit should offset the point")
{
    Ray r(make_point(0, 0, -5), make_vector(0, 0, 1));
    Sphere s;
    s.set_transform(translation(0, 0, 1));
    Intersection i(5, s);
    auto comps = i.prepare_hit_computation(r);
    REQUIRE(comps.get_over_point().z() < -detail::EPSILON / 2.0);
    REQUIRE(comps.get_point().z() > comps.get_over_point().z());
}

TEST_CASE("Pre-computing the reflection vector")
{
    Plane p;
    Ray r(make_point(0, 1, -1), make_vector(0, -std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
    Intersection i(std::sqrt(2.0), p);
    auto comps = i.prepare_hit_computation(r);
    REQUIRE(comps.get_reflect_vector() == make_vector(0, std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
}
