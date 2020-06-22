#include "catch.hpp"
#include "Canvas.h"

#include <sstream>

using namespace raytracer;

TEST_CASE("Canvas initializes to all black")
{
    Color black(0, 0, 0);
    Canvas canvas(10, 20);
    REQUIRE(canvas.getWidth() == 10);
    REQUIRE(canvas.getHeight() == 20);
    for (const auto& pixel : canvas) {
        REQUIRE(pixel == black);
    }
    REQUIRE(canvas.at(3, 4) == black);
}

TEST_CASE("Const Canvas initialized to all black")
{
    Color black(0, 0, 0);
    const Canvas canvas(15, 25);
    REQUIRE(canvas.getWidth() == 15);
    REQUIRE(canvas.getHeight() == 25);
    for (const auto& pixel : canvas) {
        REQUIRE(pixel == black);
    }
    REQUIRE(canvas.at(3, 4) == black);
}

TEST_CASE("Can set colors of pixels")
{
    Canvas canvas(10, 20);
    for (size_t x = 0; x < canvas.getWidth(); ++x) {
        for (size_t y = 0; y < canvas.getHeight(); ++y) {
            canvas.at(x, y) = Color(x, y, x+y);
        }
    }

    for (size_t x = 0; x < canvas.getWidth(); ++x) {
        for (size_t y = 0; y < canvas.getHeight(); ++y) {
            REQUIRE(canvas.at(x, y) == Color(x, y, x+y));
        }
    }
}

TEST_CASE("Invalid canvas coordinates throw exception")
{
    Canvas canvas(5, 3);
    REQUIRE_THROWS_AS(canvas.at(10, 2), std::out_of_range);
    REQUIRE_THROWS_AS(canvas.at(2, 10), std::out_of_range);
    REQUIRE_THROWS_AS(canvas.at(10, 10), std::out_of_range);
    REQUIRE_THROWS_AS(canvas.at(-1, 0), std::out_of_range);
}

TEST_CASE("Can output PPM file")
{
    Canvas canvas(5, 3);
    canvas.at(0, 0) = Color(1.5, 0, 0);
    canvas.at(2, 1) = Color(0, 0.5, 0);
    canvas.at(4, 2) = Color(-0.5, 0, 1);

    std::ostringstream out;
    canvas.writePPM(out);
    auto exp = "P3\n5 3\n255\n"
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    REQUIRE(out.str() == exp);
}

TEST_CASE("Long PPM lines wrap at 70 characters")
{
    Canvas canvas(10, 2);
    for (auto& pixel : canvas) {
        pixel = Color(1, 0.8, 0.6);
    }

    std::ostringstream out;
    canvas.writePPM(out);
    auto exp = "P3\n10 2\n255\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    REQUIRE(out.str() == exp);
}
