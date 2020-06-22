#include "catch.hpp"
#include "Color.h"

using namespace raytracer;

TEST_CASE("Color is a tuple")
{
    REQUIRE(make_color(1.5, 2.5, 3.5) == Tuple(1.5, 2.5, 3.5, 0));
}

TEST_CASE("Can add colors")
{
    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);
    REQUIRE(c1 + c2 == Color(1.6, 0.7, 1.0));
}

TEST_CASE("Can subtract colors")
{
    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);
    REQUIRE(c1 - c2 == Color(0.2, 0.5, 0.5));
}

TEST_CASE("Can multiply color by scalar")
{
    REQUIRE(Color(1, 0.2, 0.4) * 2.5 == Color(2.5, 0.5, 1.0));
}

TEST_CASE("Can multiply two colors")
{
    Color c1(1.0, 0.2, 0.4);
    Color c2(0.9, 1.0, 0.1);
    REQUIRE(c1 * c2 == Color(0.9, 0.2, 0.04));
}
