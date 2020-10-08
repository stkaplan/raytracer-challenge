#ifndef _STRIPEPATTERN_H_
#define _STRIPEPATTERN_H_

#include "Color.h"
#include "Pattern.h"
#include "Tuple.h"

#include <vector>

namespace raytracer {

class StripePattern final : public Pattern {
private:
    std::vector<Color> colors;

    bool isEqual(const Pattern& other) const override {
        return colors == static_cast<const StripePattern&>(other).colors;
    }

public:
    StripePattern()
        : colors{Color::WHITE, Color::BLACK}
    { }

    StripePattern(const std::vector<Color>& colors)
        : colors(colors)
    { }

    Color color_at(const Tuple4& point) const override;

    auto& get_colors() { return colors; }
    const auto& get_colors() const { return colors; }
};

} // namespace raytracer

#endif // _PATTERN_H_
