#include "catch.hpp"
#include "Sphere.h"

#include "Ray.h"
#include "Transformations.h"

using namespace raytracer;

TEST_CASE("Sphere has default transformation of identity matrix")
{
    Sphere s;
    REQUIRE(s.get_transform() == make_identity<double, 4>());
}

TEST_CASE("Can set transformation for sphere")
{
    auto t = translation(2, 3, 4);
    Sphere s;
    s.set_transform(t);
    REQUIRE(s.get_transform() == t);
}

TEST_CASE("Ray intersection with scaled sphere")
{
    auto origin = make_point(0, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;
    s.set_transform(scale(2, 2, 2));

    auto result = s.intersect(r);
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].get_t() == 3);
    REQUIRE(result[1].get_t() == 7);
}

TEST_CASE("Ray intersection with translated sphere")
{
    auto origin = make_point(0, 0, -5);
    auto direction = make_vector(0, 0, 1);
    Ray r(origin, direction);
    Sphere s;
    s.set_transform(translation(5, 0, 0));

    auto result = s.intersect(r);
    REQUIRE(result.size() == 0);
}

TEST_CASE("Normal on sphere at point on x-axis")
{
    Sphere s;
    auto n = s.normal_at(make_point(1, 0, 0));
    REQUIRE(n == make_vector(1, 0, 0));
    REQUIRE(n == n.normalize());
}

TEST_CASE("Normal on sphere at point on y-axis")
{
    Sphere s;
    auto n = s.normal_at(make_point(0, 1, 0));
    REQUIRE(n == make_vector(0, 1, 0));
    REQUIRE(n == n.normalize());
}

TEST_CASE("Normal on sphere at point on z-axis")
{
    Sphere s;
    auto n = s.normal_at(make_point(0, 0, 1));
    REQUIRE(n == make_vector(0, 0, 1));
    REQUIRE(n == n.normalize());
}

TEST_CASE("Normal on sphere at non-axial point")
{
    Sphere s;
    double num = std::sqrt(3.0) / 3.0;
    auto n = s.normal_at(make_point(num, num, num));
    REQUIRE(n == make_vector(num, num, num));
    REQUIRE(n == n.normalize());
}

TEST_CASE("Normal on translated sphere")
{
    Sphere s;
    s.set_transform(translation(0, 1, 0));
    auto n = s.normal_at(make_point(0, 1.70711, -0.70711));
    REQUIRE(n == make_vector(0, 0.70711, -0.70711));
}

TEST_CASE("Normal on scaled and rotated sphere")
{
    auto transform = scale(1.0, 0.5, 1.0) * rotation<Dimension::Z>(M_PI / 5.0);
    Sphere s;
    s.set_transform(transform);
    auto n = s.normal_at(make_point(0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0));
    REQUIRE(n == make_vector(0, 0.97014, -0.24254));
}

TEST_CASE("Sphere with default material")
{
    Sphere s;
    auto m = s.get_material();
    Material default_material;
    REQUIRE(m == default_material);
}

TEST_CASE("Sphere with non-default material")
{
    Sphere s;
    Material m(make_color(0.1, 0.2, 0.3), 1.5, 2.5, 3.5, 4.5);
    s.set_material(m);
    REQUIRE(s.get_material().get_color() == make_color(0.1, 0.2, 0.3));
    REQUIRE(s.get_material().get_shininess() == 4.5);
}
