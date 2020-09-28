#ifndef _PATTERN_H_
#define _PATTERN_H_

#include "Color.h"
#include "Transformations.h"
#include "Tuple.h"

namespace raytracer {

class Shape;

class Pattern {
private:
    TransformationMatrix transform;
    TransformationMatrix transform_inverse;

    virtual bool isEqual(const Pattern& other) const = 0;

public:
    Pattern() {
        set_transform(make_identity<double, 4>());
    }

    const TransformationMatrix& get_transform() const { return transform; }
    void set_transform(const TransformationMatrix& m) {
        transform = m;
        transform_inverse = transform.inverse().value();
    }

    const TransformationMatrix& get_transform_inverse() const { return transform_inverse; }

    virtual Color color_at(const Tuple4& point) const = 0;

    Color color_at_object(const Shape& object, const Tuple4& point) const;

    bool operator==(const Pattern& other) const {
        return typeid(*this) == typeid(other) && isEqual(other);
    }
};

} // namespace raytracer

#endif // _PATTERN_H_
