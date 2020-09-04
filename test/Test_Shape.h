#ifndef _TEST_TEST_SHAPE_H_
#define _TEST_TEST_SHAPE_H_

#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"
#include "Tuple.h"

namespace raytracer {

class TestShape final : public Shape {
public:
    TestShape() : Shape() { }
    mutable Ray saved_ray;

    virtual std::vector<Intersection> local_intersect([[maybe_unused]] const Ray& ray) const override {
        saved_ray = ray;
        return {};
    }

    virtual Tuple4 local_normal_at(const Tuple4& point) const override {
        return make_vector(point.x(), point.y(), point.z());
    }
};

} // namespace raytracer

#endif // _TEST_TEST_SHAPE_H_
