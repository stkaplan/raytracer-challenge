#ifndef _PATTERN_H_
#define _PATTERN_H_

#include "Color.h"
#include "Tuple.h"

namespace raytracer {

class Pattern {
private:

public:
    virtual Color color_at(const Tuple4& point) const = 0;
};

} // namespace raytracer

#endif // _PATTERN_H_
