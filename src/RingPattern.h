#ifndef _RINGPATTERN_H_
#define _RINGPATTERN_H_

#include "Color.h"
#include "Pattern.h"
#include "Tuple.h"

#include <vector>

namespace raytracer {

class RingPattern final : public Pattern {
private:
    Color color1, color2;

    bool isEqual(const Pattern& o) const override {
        auto other = static_cast<const RingPattern&>(o);
        return color1 == other.color1 && color2 == other.color2;
    }

public:
    RingPattern(const Color& color1, const Color& color2)
        : color1(color1), color2(color2)
    { }

    Color color_at(const Tuple4& point) const override;

    Color get_color1() const { return color1; }
    Color get_color2() const { return color2; }
};

} // namespace raytracer

#endif // _RINGPATTERN_H_
