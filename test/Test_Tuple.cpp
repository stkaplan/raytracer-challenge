#include "catch.hpp"
#include "common.h"
#include "Tuple.h"

using namespace raytracer;

TEST_CASE("Tuple with w=1.0 is a point")
{
    Tuple t(4.0, 5.0, 6.0, 1.0);
    REQUIRE(t.is_point());
    REQUIRE(!t.is_vector());
}

TEST_CASE("Tuple with w=0 is a vector")
{
    Tuple t(4.0, 5.0, 6.0, 0.0);
    REQUIRE(t.is_vector());
    REQUIRE(!t.is_point());
}

TEST_CASE("make_point returns a point")
{
    Tuple t = make_point(4, 5, 6);
    REQUIRE(t.is_point());
    REQUIRE(!t.is_vector());
}

TEST_CASE("make_vector returns a vector")
{
    Tuple t = make_vector(4, 5, 6);
    REQUIRE(t.is_vector());
    REQUIRE(!t.is_point());
}

TEST_CASE("Numbers within epsilon compare as equal")
{
    Tuple t1 = make_point(4, 5, 6);
    Tuple t2 = make_point(4.000001, 5.000001, 6.000001);
    REQUIRE(t1 == t2);
}

TEST_CASE("Adding two vectors gives a vector")
{
    Tuple t1 = make_vector(4, 5, 6);
    Tuple t2 = make_vector(7, 8, 9);
    Tuple sum = make_vector(11, 13, 15);
    REQUIRE(t1 + t2 == sum);
}

TEST_CASE("Adding vector and point gives a point")
{
    Tuple t1 = make_point(4, 5, 6);
    Tuple t2 = make_vector(7, 8, 9);
    Tuple sum = make_point(11, 13, 15);
    REQUIRE(t1 + t2 == sum);
}

TEST_CASE("Subtracting two points gives a vector")
{
    Tuple t1 = make_point(4, 5, 6);
    Tuple t2 = make_point(10, 12, 14);
    Tuple diff = make_vector(-6, -7, -8);
    REQUIRE(t1 - t2 == diff);
}

TEST_CASE("Subtracting vector from point gives a point")
{
    Tuple t1 = make_point(4, 5, 6);
    Tuple t2 = make_vector(1, 3, 5);
    Tuple diff = make_point(3, 2, 1);
    REQUIRE(t1 - t2 == diff);
}

TEST_CASE("Subtracting vector from vector gives a vector")
{
    Tuple t1 = make_vector(1.5, 2.5, 3.5);
    Tuple t2 = make_vector(2.1, 2.2, 2.3);
    Tuple diff = make_vector(-0.6, 0.3, 1.2);
    REQUIRE(t1 - t2 == diff);
}

TEST_CASE("Can negate tuple")
{
    Tuple t = Tuple(-1, 2, -3, 4);
    Tuple negate = Tuple(1, -2, 3, -4);
    REQUIRE(-t == negate);
}

TEST_CASE("Can multiply tuple by scalar")
{
    Tuple t = Tuple(1, 2, -3, -4);
    REQUIRE(t * 0.1 == Tuple(0.1, 0.2, -0.3, -0.4));
}

TEST_CASE("Can divide tuple by a scalar")
{
    Tuple t = Tuple(1, 2, -3, -4);
    REQUIRE(t / 0.1 == Tuple(10, 20, -30, -40));
}

TEST_CASE("Tuple magnitude gives correct value")
{
    REQUIRE(Tuple(1, 0, 0, 0).magnitude() == 1);
    REQUIRE(Tuple(0, 1, 0, 0).magnitude() == 1);
    REQUIRE(Tuple(0, 0, 1, 0).magnitude() == 1);
    REQUIRE(Tuple(0, 0, 0, 1).magnitude() == 1);
    REQUIRE(Tuple(1, 2, -3, 4.5).magnitude() == std::sqrt(34.25));
}

TEST_CASE("Tuple normalize gives correct value")
{
    REQUIRE(Tuple(4, 0, 0, 0).normalize() == Tuple(1, 0, 0, 0));
    REQUIRE(Tuple(0, 0, 0, 4).normalize() == Tuple(0, 0, 0, 1));

    double scale = 1 / std::sqrt(3000);
    REQUIRE(Tuple(10, 20, 30, 40).normalize() == Tuple(10*scale, 20*scale, 30*scale, 40*scale));

    scale = 1 / std::sqrt(0.30);
    REQUIRE(Tuple(0.4, 0.3, -0.2, -0.1).normalize() == Tuple(0.4*scale, 0.3*scale, -0.2*scale, -0.1*scale));
}

TEST_CASE("Dot product gives correct value")
{
    REQUIRE(float_equals(Tuple(1, 2, 3, 4).dot_product(Tuple(3, 4, -5, -6)), -28.0));
    REQUIRE(float_equals(Tuple(0.1, 0.2, 0.3, 0.4).dot_product(Tuple(0.3, 0.4, -0.5, -0.6)), -0.28));
}

TEST_CASE("Cross product gives correct value")
{
    Tuple t1 = make_vector(1, 2, 3);
    Tuple t2 = make_vector(2, 3, 4);
    REQUIRE(t1.cross_product(t2) == make_vector(-1, 2, -1));
    REQUIRE(t2.cross_product(t1) == make_vector(1, -2, 1));
}
