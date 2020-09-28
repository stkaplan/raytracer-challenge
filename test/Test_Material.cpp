#include "catch.hpp"
#include "Material.h"

#include "Color.h"
#include "PointLight.h"
#include "StripePattern.h"
#include "Tuple.h"

using namespace raytracer;

TEST_CASE("Default material")
{
    Material m;
    REQUIRE(m.get_color() == make_color(1, 1, 1));
    REQUIRE(m.get_ambient() == 0.1);
    REQUIRE(m.get_diffuse() == 0.9);
    REQUIRE(m.get_specular() == 0.9);
    REQUIRE(m.get_shininess() == 200);
}

TEST_CASE("Non-default material")
{
    Material m(make_color(0.5, 0.6, 0.7), 1.5, 2.5, 3.5, 4.5);
    REQUIRE(m.get_color() == make_color(0.5, 0.6, 0.7));
    REQUIRE(m.get_ambient() == 1.5);
    REQUIRE(m.get_diffuse() == 2.5);
    REQUIRE(m.get_specular() == 3.5);
    REQUIRE(m.get_shininess() == 4.5);
}

TEST_CASE("Material equality")
{
    Material m(make_color(0.5, 0.6, 0.7), 1.5, 2.5, 3.5, 4.5);
    Material m2(make_color(0.5, 0.6, 0.7), 1.5, 2.5, 3.5, 4.5);
    Material m3(make_color(0.5, 0.6, 0.7), 1.5, 2.5, 3.5, 4.6);
    REQUIRE(m == m2);
    REQUIRE(m != m3);
}

TEST_CASE("Lighting with eye between light and surface")
{
    Material m;
    auto pos = make_point(0, 0, 0);
    auto eye = make_vector(0, 0, -1);
    auto normal = make_vector(0, 0, -1);
    PointLight light(make_point(0, 0, -10), make_color(1, 1, 1));
    auto result = m.lighting(light, pos, eye, normal, false);
    REQUIRE(result == make_color(1.9, 1.9, 1.9));
}

TEST_CASE("Lighting with eye between light and surface, eye offset 45 degrees")
{
    Material m;
    auto pos = make_point(0, 0, 0);
    auto eye = make_vector(0, std::sqrt(2.0)/2.0, -std::sqrt(2.0)/2.0);
    auto normal = make_vector(0, 0, -1);
    PointLight light(make_point(0, 0, -10), make_color(1, 1, 1));
    auto result = m.lighting(light, pos, eye, normal, false);
    REQUIRE(result == make_color(1.0, 1.0, 1.0));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45 degrees")
{
    Material m;
    auto pos = make_point(0, 0, 0);
    auto eye = make_vector(0, 0, -1);
    auto normal = make_vector(0, 0, -1);
    PointLight light(make_point(0, 10, -10), make_color(1, 1, 1));
    auto result = m.lighting(light, pos, eye, normal, false);
    REQUIRE(result == make_color(0.7364, 0.7364, 0.7364));
}

TEST_CASE("Lighting with eye in path of reflection vcetor")
{
    Material m;
    auto pos = make_point(0, 0, 0);
    auto eye = make_vector(0, -std::sqrt(2.0)/2.0, -std::sqrt(2.0)/2.0);
    auto normal = make_vector(0, 0, -1);
    PointLight light(make_point(0, 10, -10), make_color(1, 1, 1));
    auto result = m.lighting(light, pos, eye, normal, false);
    REQUIRE(result == make_color(1.6364, 1.6364, 1.6364));
}

TEST_CASE("Lighting with light behind surface")
{
    Material m;
    auto pos = make_point(0, 0, 0);
    auto eye = make_vector(0, 0, -1);
    auto normal = make_vector(0, 0, -1);
    PointLight light(make_point(0, 0, 10), make_color(1, 1, 1));
    auto result = m.lighting(light, pos, eye, normal, false);
    REQUIRE(result == make_color(0.1, 0.1, 0.1));
}

TEST_CASE("Lighting with surface in shadow")
{
    Material m;
    auto pos = make_point(0, 0, 0);
    auto eye = make_vector(0, 0, -1);
    auto normal = make_vector(0, 0, -1);
    PointLight light(make_point(0, 0, -10), make_color(1, 1, 1));
    bool in_shadow = true;
    auto result = m.lighting(light, pos, eye, normal, in_shadow);
    REQUIRE(result == make_color(0.1, 0.1, 0.1));
}

TEST_CASE("Lighting with a pattern applied")
{
    auto pattern = std::make_shared<StripePattern>();
    Material m(make_color(1, 1, 1), 1.0, 0.0, 0.0, Material::DEFAULT_SHININESS, pattern);
    auto eye_vector = make_vector(0, 0, -1);
    auto normal_vector = make_vector(0, 0, -1);
    PointLight light(make_point(0, 0, -10), make_color(1, 1, 1));
    auto c1 = m.lighting(light, make_point(0.9, 0, 0), eye_vector, normal_vector, false);
    auto c2 = m.lighting(light, make_point(1.1, 0, 0), eye_vector, normal_vector, false);
    REQUIRE(c1 == make_color(1, 1, 1));
    REQUIRE(c2 == make_color(0, 0, 0));
}
