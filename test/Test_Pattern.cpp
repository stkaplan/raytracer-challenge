#include "catch.hpp"
#include "Pattern.h"
#include "Sphere.h"

#include "StripePattern.h"

using namespace raytracer;

TEST_CASE("Creating a stripe pattern")
{
    const StripePattern pattern;
    auto& colors = pattern.get_colors();
    REQUIRE(colors.size() == 2);
    REQUIRE(colors[0] == Color::WHITE);
    REQUIRE(colors[1] == Color::BLACK);
}

TEST_CASE("A stripe pattern is constant in y")
{
    const StripePattern pattern;
    REQUIRE(pattern.color_at(make_point(0, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0, 1, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0, 2, 0)) == Color::WHITE);
}

TEST_CASE("A stripe pattern is constant in z")
{
    const StripePattern pattern;
    REQUIRE(pattern.color_at(make_point(0, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0, 0, 1)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0, 0, 2)) == Color::WHITE);
}

TEST_CASE("A stripe pattern alternates in x")
{
    const StripePattern pattern;
    REQUIRE(pattern.color_at(make_point(0, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0.9, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(1, 0, 0)) == Color::BLACK);
    REQUIRE(pattern.color_at(make_point(-0.1, 0, 0)) == Color::BLACK);
    REQUIRE(pattern.color_at(make_point(-1, 0, 0)) == Color::BLACK);
    REQUIRE(pattern.color_at(make_point(-1.1, 0, 0)) == Color::WHITE);
}

TEST_CASE("Stripes with object transform")
{
    Sphere s;
    s.set_transform(scale(2, 2, 2));

    StripePattern p;

    REQUIRE(p.color_at_object(s, make_point(1.5, 0, 0)) == Color::WHITE);
}

TEST_CASE("Stripes with pattern transform")
{
    Sphere s;

    StripePattern p;
    p.set_transform(scale(2, 2, 2));

    REQUIRE(p.color_at_object(s, make_point(1.5, 0, 0)) == Color::WHITE);
}

TEST_CASE("Stripes with both object and pattern transform")
{
    Sphere s;
    s.set_transform(scale(2, 2, 2));

    StripePattern p;
    p.set_transform(translation(0.5, 0, 0));

    REQUIRE(p.color_at_object(s, make_point(2.5, 0, 0)) == Color::WHITE);
}
