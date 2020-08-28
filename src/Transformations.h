#ifndef _TRANSFORMATIONS_H_
#define _TRANSFORMATIONS_H_

#include "Matrix.h"
#include <cmath>

namespace raytracer {

using TransformationMatrix = Matrix<double, 4, 4>;

constexpr TransformationMatrix translation(double x, double y, double z)
{
    return {{
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1},
    }};
}

constexpr TransformationMatrix scale(double x, double y, double z)
{
    return {{
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1},
    }};
}

enum class Dimension { X, Y, Z };

// Can't be constexpr because of sin/cos.
template <Dimension D>
TransformationMatrix rotation(double radians)
{
    TransformationMatrix matrix = {{{0}}};

    auto dim = static_cast<size_t>(D);
    auto neg_rot = (dim+1)%3; // Row getting the -sin rotation
    auto pos_rot = (dim+2)%3; // Row getting the +sin rotation

    matrix[dim][dim] = 1;
    matrix[neg_rot][neg_rot] = std::cos(radians);
    matrix[neg_rot][pos_rot] = -std::sin(radians);
    matrix[pos_rot][neg_rot] = std::sin(radians);
    matrix[pos_rot][pos_rot] = std::cos(radians);
    matrix[3][3] = 1;
    return matrix;
}

constexpr TransformationMatrix skew(double x_y, double x_z,
                                    double y_x, double y_z,
                                    double z_x, double z_y)
{
    return {{
        {1,   x_y, x_z, 0},
        {y_x, 1,   y_z, 0},
        {z_x, z_y, 1,   0},
        {0,   0,   0,   1},
    }};
}

// Can't be constexpr because of normalize()
inline TransformationMatrix view_transform(
        const Tuple4& from, const Tuple4& to, const Tuple4& up)
{
    auto forward = (to - from).normalize();
    auto left = forward.cross_product(up.normalize());
    auto true_up = left.cross_product(forward);

    TransformationMatrix orientation = {{{0}}};
    for (size_t i = 0; i < 3; ++i) {
        orientation[0][i] = left[i];
        orientation[1][i] = true_up[i];
        orientation[2][i] = -forward[i];
    }
    orientation[3][3] = 1;
    return orientation * translation(-from.x(), -from.y(), -from.z());
}

} // namespace raytracer

#endif // _TRANSFORMATIONS_H_
