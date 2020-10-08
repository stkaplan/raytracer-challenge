#ifndef _TEST_TEST_PATTERN_H_
#define _TEST_TEST_PATTERN_H_

#include "Pattern.h"

namespace raytracer {

class TestPattern final : public Pattern {
private:
    bool isEqual(const Pattern&) const override { return true; }
public:
    TestPattern() : Pattern() { }

    Color color_at(const Tuple4& point) const override {
        return make_color(point.x(), point.y(), point.z());
    }
};

} // namespace raytracer

#endif // _TEST_TEST_SHAPE_H_
