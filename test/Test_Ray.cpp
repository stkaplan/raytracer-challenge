#include "catch.hpp"
#include "Ray.h"

#include "Intersection.h"
#include "Sphere.h"
#include "Transformations.h"
#include "Tuple.h"

using namespace raytracer;

TEST_CASE("Can create an query a ray")
{
    auto origin = make_point(1, 2, 3);
    auto direction = make_point(4, 5, 6);
    Ray r(origin, direction);
    REQUIRE(r.get_origin() == origin);
    REQUIRE(r.get_direction() == direction);
}

TEST_CASE("Can compute point from a distance")
{
    auto origin = make_point(2, 3, 4);
    auto direction = make_vector(1, 0, 0);
    Ray r(origin, direction);

    REQUIRE(r.position(0) == make_point(2, 3, 4));
    REQUIRE(r.position(1) == make_point(3, 3, 4));
    REQUIRE(r.position(-1) == make_point(1, 3, 4));
    REQUIRE(r.position(2.5) == make_point(4.5, 3, 4));
}

TEST_CASE("Ray intersects sphere at two points")
{
    auto origin = make_point(0, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;

    auto result = s.intersect(r);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].get_t() == 4.0);
    REQUIRE(result[1].get_t() == 6.0);
}

TEST_CASE("Ray intersecting sphere at tangent returns same point twice")
{
    auto origin = make_point(0, 1, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;

    auto result = s.intersect(r);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].get_t() == 5.0);
    REQUIRE(result[1].get_t() == 5.0);
}

TEST_CASE("Ray missing sphere returns no points")
{
    auto origin = make_point(0, 2, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;

    auto result = s.intersect(r);
    REQUIRE(result.size() == 0);
}

TEST_CASE("Ray originating inside sphere includes points in both directions")
{
    auto origin = make_point(0, 0, 0);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;

    auto result = s.intersect(r);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].get_t() == -1.0);
    REQUIRE(result[1].get_t() == 1.0);
}

TEST_CASE("Ray in front of sphere returns two negative points")
{
    auto origin = make_point(0, 0, 5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;

    auto result = s.intersect(r);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].get_t() == -6.0);
    REQUIRE(result[1].get_t() == -4.0);
}

TEST_CASE("Intersect sets the object of intersection")
{
    auto origin = make_point(0, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;

    auto result = s.intersect(r);
    REQUIRE(result.size() == 2);
    REQUIRE(&result[0].get_object() == &s);
    REQUIRE(&result[1].get_object() == &s);
}

TEST_CASE("Can translate a ray")
{
    auto origin = make_point(1, 2, 3);
    auto direction = make_vector(0, 1, 0);
    Ray r(origin, direction);

    auto m = translation(3, 4, 5);
    auto r2 = r.transform(m);
    REQUIRE(r2.get_origin() == make_point(4, 6, 8));
    REQUIRE(r2.get_direction() == make_vector(0, 1, 0));
}

TEST_CASE("Can scale a ray")
{
    auto origin = make_point(1, 2, 3);
    auto direction = make_vector(0, 1, 0);
    Ray r(origin, direction);

    auto m = scale(2, 3, 4);
    auto r2 = r.transform(m);
    REQUIRE(r2.get_origin() == make_point(2, 6, 12));
    REQUIRE(r2.get_direction() == make_vector(0, 3, 0));
}
