#ifndef _CANNON_PROJECTILE_H_
#define _CANNON_PROJECTILE_H_

#include "Tuple.h"

namespace raytracer {

class Projectile {
private:
    Tuple position;
    Tuple velocity;

public:
    constexpr Projectile(const Tuple& position, const Tuple& velocity)
            : position(position), velocity(velocity) {
        if (!position.is_point()) {
            throw std::invalid_argument("position must be a point");
        }
        if (!velocity.is_vector()) {
            throw std::invalid_argument("velocity must be a vector");
        }
    }

    constexpr const Tuple& get_position() const { return position; }
    constexpr const Tuple& get_velocity() const { return velocity; }
};

} // namespace raytracer

#endif // _CANNON_PROJECTILE_H_
