#include "catch.hpp"
#include "Transformations.h"

#include <cmath>

using namespace raytracer;

TEST_CASE("Multiplying by translation matrix moves a point")
{
    auto transform = translation(5, -3, 2);
    auto point = make_point(-3, 4, 5);
    auto result = make_point(2, 1, 7);
    REQUIRE(transform * point == result);
}

TEST_CASE("Multiplying by inverse of translation matrix moves point in reverse")
{
    auto inverse = translation(5, -3, 2).inverse();
    REQUIRE(inverse.has_value());
    auto transform = inverse.value();
    auto point = make_point(-3, 4, 5);
    auto result = make_point(-8, 7, 3);
    REQUIRE(transform * point == result);
}

TEST_CASE("Multiplying by translation matrix does not move a vector")
{
    auto transform = translation(5, -3, 2);
    auto vector = make_vector(-3, 4, 5);
    REQUIRE(transform * vector == vector);
}

TEST_CASE("Can scale a point")
{
    auto transform = scale(2, 3, 4);
    auto point = make_point(-4, 6, 8);
    auto result = make_point(-8, 18, 32);
    REQUIRE(transform * point == result);
}

TEST_CASE("Can scale a vector")
{
    auto transform = scale(2, 3, 4);
    auto vector = make_vector(-4, 6, 8);
    auto result = make_vector(-8, 18, 32);
    REQUIRE(transform * vector == result);
}

TEST_CASE("Inverse of scaling matrix applies inverse scale")
{
    auto inverse = scale(2, 3, 4).inverse();
    REQUIRE(inverse.has_value());
    auto transform = inverse.value();
    auto vector = make_vector(-4, 6, 8);
    auto result = make_vector(-2, 2, 2);
    REQUIRE(transform * vector == result);
}

TEST_CASE("Reflection is scaling by a negative value")
{
    auto transform = scale(-1, 1, 1);
    auto point = make_point(2, 3, 4);
    auto result = make_point(-2, 3, 4);
    REQUIRE(transform * point == result);
}

TEST_CASE("Can rotate around x-axis")
{
    auto point = make_point(0, 1, 0);

    auto half_quarter = rotation<Dimension::X>(M_PI / 4);
    auto half_quarter_result = make_point(0, std::sqrt(2)/2, std::sqrt(2)/2);
    REQUIRE(half_quarter * point == half_quarter_result);

    auto full_quarter = rotation<Dimension::X>(M_PI / 2);
    auto full_quarter_result = make_point(0, 0, 1);
    REQUIRE(full_quarter * point == full_quarter_result);
}

TEST_CASE("Inverse of x-rotation goes in opposite direction")
{
    auto point = make_point(0, 1, 0);

    auto inverse = rotation<Dimension::X>(M_PI / 4).inverse();
    REQUIRE(inverse.has_value());
    auto half_quarter = inverse.value();

    auto half_quarter_result = make_point(0, std::sqrt(2)/2, -std::sqrt(2)/2);
    REQUIRE(half_quarter * point == half_quarter_result);
}

TEST_CASE("Can rotate around y-axis")
{
    auto point = make_point(0, 0, 1);

    auto half_quarter = rotation<Dimension::Y>(M_PI / 4);
    auto half_quarter_result = make_point(std::sqrt(2)/2, 0, std::sqrt(2)/2);
    REQUIRE(half_quarter * point == half_quarter_result);

    auto full_quarter = rotation<Dimension::Y>(M_PI / 2);
    auto full_quarter_result = make_point(1, 0, 0);
    REQUIRE(full_quarter * point == full_quarter_result);
}

TEST_CASE("Inverse of y-rotation goes in opposite direction")
{
    auto point = make_point(0, 0, 1);

    auto inverse = rotation<Dimension::Y>(M_PI / 4).inverse();
    REQUIRE(inverse.has_value());
    auto half_quarter = inverse.value();

    auto half_quarter_result = make_point(-std::sqrt(2)/2, 0, std::sqrt(2)/2);
    REQUIRE(half_quarter * point == half_quarter_result);
}

TEST_CASE("Can rotate around z-axis")
{
    auto point = make_point(0, 1, 0);

    auto half_quarter = rotation<Dimension::Z>(M_PI / 4);
    auto half_quarter_result = make_point(-std::sqrt(2)/2, std::sqrt(2)/2, 0);
    REQUIRE(half_quarter * point == half_quarter_result);

    auto full_quarter = rotation<Dimension::Z>(M_PI / 2);
    auto full_quarter_result = make_point(-1, 0, 0);
    REQUIRE(full_quarter * point == full_quarter_result);
}

TEST_CASE("Inverse of z-rotation goes in opposite direction")
{
    auto point = make_point(0, 1, 0);

    auto inverse = rotation<Dimension::Z>(M_PI / 4).inverse();
    REQUIRE(inverse.has_value());
    auto half_quarter = inverse.value();

    auto half_quarter_result = make_point(std::sqrt(2)/2, std::sqrt(2)/2, 0);
    REQUIRE(half_quarter * point == half_quarter_result);
}

TEST_CASE("Shearing transformation moves x in proportion to y")
{
    auto transform = skew(1, 0, 0, 0, 0, 0);
    auto point = make_point(2, 3, 4);
    auto result = make_point(5, 3, 4);
    REQUIRE(transform * point == result);
}

TEST_CASE("Shearing transformation moves x in proportion to z")
{
    auto transform = skew(0, 1, 0, 0, 0, 0);
    auto point = make_point(2, 3, 4);
    auto result = make_point(6, 3, 4);
    REQUIRE(transform * point == result);
}

TEST_CASE("Shearing transformation moves y in proportion to x")
{
    auto transform = skew(0, 0, 1, 0, 0, 0);
    auto point = make_point(2, 3, 4);
    auto result = make_point(2, 5, 4);
    REQUIRE(transform * point == result);
}

TEST_CASE("Shearing transformation moves y in proportion to z")
{
    auto transform = skew(0, 0, 0, 1, 0, 0);
    auto point = make_point(2, 3, 4);
    auto result = make_point(2, 7, 4);
    REQUIRE(transform * point == result);
}

TEST_CASE("Shearing transformation moves z in proportion to x")
{
    auto transform = skew(0, 0, 0, 0, 1, 0);
    auto point = make_point(2, 3, 4);
    auto result = make_point(2, 3, 6);
    REQUIRE(transform * point == result);
}

TEST_CASE("Shearing transformation moves z in proportion to y")
{
    auto transform = skew(0, 0, 0, 0, 0, 1);
    auto point = make_point(2, 3, 4);
    auto result = make_point(2, 3, 7);
    REQUIRE(transform * point == result);
}

TEST_CASE("Individual transformations are applied in sequence")
{
    auto p = make_point(1, 0, 1);
    auto A = rotation<Dimension::X>(M_PI / 2);
    auto B = scale(5, 5, 5);
    auto C = translation(10, 5, 7);

    auto p2 = A * p;
    REQUIRE(p2 == make_point(1, -1, 0));

    auto p3 = B * p2;
    REQUIRE(p3 == make_point(5, -5, 0));

    auto p4 = C * p3;
    REQUIRE(p4 == make_point(15, 0, 7));
}

TEST_CASE("Chained transformations are applied in reverse order")
{
    auto p = make_point(1, 0, 1);
    auto A = rotation<Dimension::X>(M_PI / 2);
    auto B = scale(5, 5, 5);
    auto C = translation(10, 5, 7);
    REQUIRE((C*B*A) * p == make_point(15, 0, 7));

}

TEST_CASE("Can use apply() to chain transformations")
{
    auto p = make_point(1, 0, 1);
    auto transform = rotation<Dimension::X>(M_PI / 2)
                    .apply(scale(5, 5, 5))
                    .apply(translation(10, 5, 7));
    REQUIRE(transform * p == make_point(15, 0, 7));
}
