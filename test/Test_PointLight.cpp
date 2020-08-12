#include "catch.hpp"
#include "PointLight.h"

#include "Color.h"
#include "Tuple.h"

using namespace raytracer;

TEST_CASE("Point light has position and intensity")
{
    auto position = make_point(0, 0, 0);
    auto intensity = make_color(1, 1, 1);
    PointLight light(position, intensity);
    REQUIRE(light.get_position() == position);
    REQUIRE(light.get_intensity() == intensity);
}
