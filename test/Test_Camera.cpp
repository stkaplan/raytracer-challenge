#include "catch.hpp"
#include "Camera.h"

#include "Ray.h"
#include "Transformations.h"
#include "World.h"

using namespace raytracer;

TEST_CASE("Constructing a camera")
{
    Camera c(160, 120, M_PI_2);
    REQUIRE(c.get_horizontal_size() == 160);
    REQUIRE(c.get_vertical_size() == 120);
    REQUIRE(c.get_field_of_view() == M_PI_2);
    REQUIRE(c.get_transform() == make_identity<double, 4>());
}

TEST_CASE("Pixel size for horizontal canvas")
{
    Camera c(200, 125, M_PI_2);
    REQUIRE(c.get_pixel_size() == Approx(0.01));
}

TEST_CASE("Pixel size for vertical canvas")
{
    Camera c(125, 200, M_PI_2);
    REQUIRE(c.get_pixel_size() == Approx(0.01));
}

TEST_CASE("Constructing ray through center of canvas")
{
    Camera c(201, 101, M_PI_2);
    Ray r = c.ray_for_pixel(100, 50);
    REQUIRE(r.get_origin() == make_point(0, 0, 0));
    REQUIRE(r.get_direction() == make_vector(0, 0, -1));
}

TEST_CASE("Constructing ray through corner of canvas")
{
    Camera c(201, 101, M_PI_2);
    Ray r = c.ray_for_pixel(0, 0);
    REQUIRE(r.get_origin() == make_point(0, 0, 0));
    REQUIRE(r.get_direction() == make_vector(0.66519, 0.33259, -0.66851));
}

TEST_CASE("Constructing ray when camera is transformed")
{
    TransformationMatrix m = rotation<Dimension::Y>(M_PI_4) * translation(0, -2, 5);
    Camera c(201, 101, M_PI_2, m);
    Ray r = c.ray_for_pixel(100, 50);
    REQUIRE(r.get_origin() == make_point(0, 2, -5));
    REQUIRE(r.get_direction() == make_vector(std::sqrt(2)/2, 0, -std::sqrt(2)/2));
}

TEST_CASE("Rendering world with default camera")
{
    World w = World::default_world();
    auto from = make_point(0, 0, -5);
    auto to = make_point(0, 0, 0);
    auto up = make_point(0, 1, 0);
    auto transform = view_transform(from, to, up);
    Camera c(11, 11, M_PI_2, transform);

    auto image = c.render(w);
    REQUIRE(image.at(5, 5) == make_color(0.38066, 0.47583, 0.2855));
}
