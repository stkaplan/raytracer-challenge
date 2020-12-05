#include "catch.hpp"
#include "Cube.h"

#include "Ray.h"
#include "Transformations.h"

using namespace raytracer;

TEST_CASE("Ray intersects cube")
{
    Cube c;
    struct Test {
        Ray ray;
        double t1;
        double t2;
    };
    std::vector<Test> tests = {
        {{make_point(5, 0.5, 0), make_vector(-1, 0, 0)}, 4, 6},
        {{make_point(-5, 0.5, 0), make_vector(1, 0, 0)}, 4, 6},
        {{make_point(0.5, 5, 0), make_vector(0, -1, 0)}, 4, 6},
        {{make_point(0.5, -5, 0), make_vector(0, 1, 0)}, 4, 6},
        {{make_point(0.5, 0, 5), make_vector(0, 0, -1)}, 4, 6},
        {{make_point(0.5, 0, -5), make_vector(0, 0, 1)}, 4, 6},
        {{make_point(0, 0.5, 0), make_vector(0, 0, 1)}, -1, 1},
    };

    for (const auto& test : tests) {
        auto xs = c.local_intersect(test.ray);
        std::vector<Intersection> exp = {{test.t1, c}, {test.t2, c}};
        REQUIRE(xs == exp);
    }
}

TEST_CASE("Ray misses cube")
{
    Cube c;
    std::vector<Ray> rays = {
        {make_point(-2, 0, 0), make_vector(0.2673, 0.5345, 0.8018)},
        {make_point(0, -2, 0), make_vector(0.8018, 0.2673, 0.5345)},
        {make_point(0, 0, -2), make_vector(0.5345, 0.8018, 0.2673)},
        {make_point(2, 0, 2), make_vector(0, 0, -1)},
        {make_point(0, 2, 2), make_vector(0, -1, 0)},
        {make_point(2, 2, 0), make_vector(-1, 0, 0)},
    };

    for (const auto& ray : rays) {
        auto xs = c.local_intersect(ray);
        std::vector<Intersection> exp = {};
        REQUIRE(xs == exp);
    }
}

TEST_CASE("Normal on surface of cube")
{
    Cube c;
    struct Test {
        Tuple4 point;
        Tuple4 normal;
    };
    std::vector<Test> tests = {
        {make_point(1, 0.5, -0.8), make_vector(1, 0, 0)},
        {make_point(-1, 0.2, 0.9), make_vector(-1, 0, 0)},
        {make_point(-0.4, 1, -0.1), make_vector(0, 1, 0)},
        {make_point(0.3, -1, -0.7), make_vector(0, -1, 0)},
        {make_point(-0.6, 0.3, 1), make_vector(0, 0, 1)},
        {make_point(0.4, 0.4, -1), make_vector(0, 0, -1)},
        {make_point(1, 1, 1), make_vector(1, 0, 0)},
        {make_point(-1, -1, -1), make_vector(-1, 0, 0)},
    };

    for (const auto& test : tests) {
        REQUIRE(c.local_normal_at(test.point) == test.normal);
    }
}
