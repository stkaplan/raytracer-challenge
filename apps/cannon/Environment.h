#ifndef _CANNON_ENVIRONMENT_H_
#define _CANNON_ENVIRONMENT_H_

#include "Tuple.h"

namespace raytracer {

class Environment {
private:
    Tuple gravity;
    Tuple wind;

public:
    constexpr Environment(const Tuple& gravity, const Tuple& wind)
            : gravity(gravity), wind(wind) {
        if (!gravity.is_vector()) {
            throw std::invalid_argument("gravity must be a vector");
        }
        if (!wind.is_vector()) {
            throw std::invalid_argument("wind must be a vector");
        }
    }

    constexpr const Tuple& get_gravity() const { return gravity; }
    constexpr const Tuple& get_wind() const { return wind; }
};

} // namespace raytracer

#endif // _CANNON_ENVIRONMENT_H_
