#ifndef _PATTERN_H_
#define _PATTERN_H_

#include "Color.h"
#include "Tuple.h"

namespace raytracer {

class Pattern {
private:
    virtual bool isEqual(const Pattern& other) const = 0;

public:
    virtual Color color_at(const Tuple4& point) const = 0;

    bool operator==(const Pattern& other) const {
        return typeid(*this) == typeid(other) && isEqual(other);
    }
};

} // namespace raytracer

#endif // _PATTERN_H_
