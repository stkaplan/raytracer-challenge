#include "catch.hpp"
#include "Pattern.h"
#include "Sphere.h"

#include "Test_Pattern.h"
#include "GradientPattern.h"
#include "StripePattern.h"

#include "Color.h"
#include "Transformations.h"

using namespace raytracer;

TEST_CASE("Default pattern transformation")
{
    TestPattern pattern;
    REQUIRE(pattern.get_transform() == make_identity<double, 4>());
}

TEST_CASE("Assigning a transformation")
{
    TestPattern pattern;
    TransformationMatrix transform = translation(1, 2, 3);
    pattern.set_transform(transform);
    REQUIRE(pattern.get_transform() == transform);
    REQUIRE(pattern.get_transform_inverse() == transform.inverse().value());
}

TEST_CASE("Pattern with object transformation")
{
    Sphere sphere;
    sphere.set_transform(scale(2, 2, 2));

    TestPattern pattern;

    auto color = make_color(1, 1.5, 2);
    auto point = make_point(2, 3, 4);
    REQUIRE(pattern.color_at_object(sphere, point) == color);
}

TEST_CASE("Pattern with pattern transformation")
{
    Sphere sphere;

    TestPattern pattern;
    pattern.set_transform(scale(2, 2, 2));

    auto color = make_color(1, 1.5, 2);
    auto point = make_point(2, 3, 4);
    REQUIRE(pattern.color_at_object(sphere, point) == color);
}

TEST_CASE("Pattern with both object and pattern transformation")
{
    Sphere sphere;
    sphere.set_transform(scale(2, 2, 2));

    TestPattern pattern;
    pattern.set_transform(translation(0.5, 1, 1.5));

    auto color = make_color(0.75, 0.5, 0.25);
    auto point = make_point(2.5, 3, 3.5);
    REQUIRE(pattern.color_at_object(sphere, point) == color);
}

TEST_CASE("Creating a stripe pattern")
{
    const StripePattern pattern;
    auto& colors = pattern.get_colors();
    REQUIRE(colors.size() == 2);
    REQUIRE(colors[0] == Color::WHITE);
    REQUIRE(colors[1] == Color::BLACK);
}

TEST_CASE("Stripe pattern is constant in y")
{
    const StripePattern pattern;
    REQUIRE(pattern.color_at(make_point(0, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0, 1, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0, 2, 0)) == Color::WHITE);
}

TEST_CASE("Stripe pattern is constant in z")
{
    const StripePattern pattern;
    REQUIRE(pattern.color_at(make_point(0, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0, 0, 1)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0, 0, 2)) == Color::WHITE);
}

TEST_CASE("Stripe pattern alternates in x")
{
    const StripePattern pattern;
    REQUIRE(pattern.color_at(make_point(0, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0.9, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(1, 0, 0)) == Color::BLACK);
    REQUIRE(pattern.color_at(make_point(-0.1, 0, 0)) == Color::BLACK);
    REQUIRE(pattern.color_at(make_point(-1, 0, 0)) == Color::BLACK);
    REQUIRE(pattern.color_at(make_point(-1.1, 0, 0)) == Color::WHITE);
}

TEST_CASE("Gradient pattern linearly interpolates between colors")
{
    GradientPattern pattern(Color::WHITE, Color::BLACK);
    REQUIRE(pattern.color_at(make_point(0, 0, 0)) == Color::WHITE);
    REQUIRE(pattern.color_at(make_point(0.25, 0, 0)) == make_color(0.75, 0.75, 0.75));
    REQUIRE(pattern.color_at(make_point(0.5, 0, 0)) == make_color(0.5, 0.5, 0.5));
    REQUIRE(pattern.color_at(make_point(0.75, 0, 0)) == make_color(0.25, 0.25, 0.25));
}
