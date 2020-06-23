#ifndef _CANNON_PROJECTILE_H_
#define _CANNON_PROJECTILE_H_

#include "Tuple.h"

namespace raytracer {

class Projectile {
private:
    Tuple4 position;
    Tuple4 velocity;

public:
    constexpr Projectile(const Tuple4& position, const Tuple4& velocity)
            : position(position), velocity(velocity) {
        if (!position.is_point()) {
            throw std::invalid_argument("position must be a point");
        }
        if (!velocity.is_vector()) {
            throw std::invalid_argument("velocity must be a vector");
        }
    }

    constexpr const auto& get_position() const { return position; }
    constexpr const auto& get_velocity() const { return velocity; }
};

} // namespace raytracer

#endif // _CANNON_PROJECTILE_H_
