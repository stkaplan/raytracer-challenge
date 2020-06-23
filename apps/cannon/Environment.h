#ifndef _CANNON_ENVIRONMENT_H_
#define _CANNON_ENVIRONMENT_H_

#include "Tuple.h"

namespace raytracer {

class Environment {
private:
    Tuple4 gravity;
    Tuple4 wind;

public:
    constexpr Environment(const Tuple4& gravity, const Tuple4& wind)
            : gravity(gravity), wind(wind) {
        if (!gravity.is_vector()) {
            throw std::invalid_argument("gravity must be a vector");
        }
        if (!wind.is_vector()) {
            throw std::invalid_argument("wind must be a vector");
        }
    }

    constexpr const auto& get_gravity() const { return gravity; }
    constexpr const auto& get_wind() const { return wind; }
};

} // namespace raytracer

#endif // _CANNON_ENVIRONMENT_H_
