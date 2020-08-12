#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "Color.h"
#include "Tuple.h"

namespace raytracer {

class PointLight {
private:
    Tuple4 position;
    Color intensity;

public:
    PointLight(const Tuple4& position, const Color& intensity)
        : position(position), intensity(intensity)
    { }

    bool operator==(const PointLight& other) const = default;

    const Tuple4& get_position() const { return position; }
    const Color& get_intensity() const { return intensity; }
};

} // namespace raytracer

#endif // _POINTLIGHT_H_
