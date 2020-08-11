#ifndef _TUPLE_H_
#define _TUPLE_H_

#include "common.h"

#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>

namespace {
template <typename T, size_t N, class Op>
constexpr std::array<T, N> unary_operator(const std::array<T, N>& arr1, Op op)
{
    // TODO: Is there a better way to do this?
    std::array<T, N> ret;
    for (size_t i = 0; i < N; i++) {
        ret[i] = op(arr1[i]);
    }
    return ret;
}

template <typename T, size_t N, class Op>
constexpr std::array<T, N> binary_operator(const std::array<T, N>& arr1, const std::array<T, N>& arr2, Op op)
{
    // TODO: Is there a better way to do this?
    std::array<T, N> ret;
    for (size_t i = 0; i < N; i++) {
        ret[i] = op(arr1[i], arr2[i]);
    }
    return ret;
}

template <typename T, size_t N>
constexpr std::array<T, N> operator+(const std::array<T, N>& arr1, const std::array<T, N>& arr2)
{
    return binary_operator(arr1, arr2, std::plus<T>());
}

template <typename T, size_t N>
constexpr std::array<T, N> operator-(const std::array<T, N>& arr1, const std::array<T, N>& arr2)
{
    return binary_operator(arr1, arr2, std::minus<T>());
}

template <typename T, size_t N>
constexpr std::array<T, N> operator-(const std::array<T, N>& arr1)
{
    return unary_operator(arr1, std::negate<T>());
}

template <typename T, size_t N, class Op>
constexpr std::array<T, N> binary_operator(const std::array<T, N>& arr1, const T scalar, Op op)
{
    // TODO: Is there a better way to do this?
    std::array<T, N> ret;
    for (size_t i = 0; i < N; i++) {
        ret[i] = op(arr1[i], scalar);
    }
    return ret;
}

template <typename T, size_t N>
constexpr std::array<T, N> operator*(const std::array<T, N>& arr1, const T scalar)
{
    return binary_operator(arr1, scalar, std::multiplies<T>());
}

template <typename T, size_t N>
constexpr std::array<T, N> operator/(const std::array<T, N>& arr1, const T scalar)
{
    return binary_operator(arr1, scalar, std::divides<T>());
}

} // anonymous namespace

namespace raytracer {

template <typename T, size_t N>
class Tuple {
public:
    using element_type = T;
    using elements_type = std::array<element_type, N>;

private:
    elements_type elements;

public:
    static constexpr T vector_marker = 0.0;
    static constexpr T point_marker = 1.0;

    template <size_t M = N>
    constexpr typename std::enable_if_t<M >= 1, T&>
    x() { return elements[0]; }
    template <size_t M = N>
    constexpr typename std::enable_if_t<M >= 1, const T&>
    x() const { return elements[0]; }

    template <size_t M = N>
    constexpr typename std::enable_if_t<M >= 2, T&>
    y() { return elements[1]; }
    template <size_t M = N>
    constexpr typename std::enable_if_t<M >= 2, const T&>
    y() const { return elements[1]; }

    template <size_t M = N>
    constexpr typename std::enable_if_t<M >= 3, T&>
    z() { return elements[2]; }
    template <size_t M = N>
    constexpr typename std::enable_if_t<M >= 3, const T&>
    z() const { return elements[2]; }

    template <size_t M = N>
    constexpr typename std::enable_if_t<M >= 4, T&>
    w() { return elements[3]; }
    template <size_t M = N>
    constexpr typename std::enable_if_t<M >= 4, const T&>
    w() const { return elements[3]; }

    constexpr Tuple() { }
    constexpr Tuple(const elements_type& elements)
        : elements(elements) { }
    constexpr Tuple(const T(&init)[N]) {
        std::copy(std::begin(init), std::end(init), elements.begin());
    }

    constexpr T& operator[](size_t i) { return elements[i]; }
    constexpr const T& operator[](size_t i) const { return elements[i]; }

    constexpr bool operator==(const Tuple& other) const {
        return std::equal(elements.cbegin(), elements.cend(),
                          other.elements.cbegin(), other.elements.cend(),
                          float_equals<element_type, element_type>);
    }

    constexpr Tuple operator+(const Tuple& other) const {
        return {elements + other.elements};
    }
    constexpr Tuple operator-(const Tuple& other) const {
        return {elements - other.elements};
    }
    constexpr Tuple operator-() const {
        return {-elements};
    }
    constexpr Tuple operator*(const element_type scalar) const {
        return {elements * scalar};
    }
    constexpr Tuple operator/(const element_type scalar) const {
        return {elements / scalar};
    }

    friend std::ostream& operator<<(std::ostream& os, const Tuple& t) {
        os << "Tuple(";
        for (size_t i = 0; i < t.elements.size(); ++i) {
            os << t.elements[i];
            if (i != t.elements.size() - 1) os << ", ";
        }
        os << ")";
        return os;
    }

    constexpr bool is_point() const {
        return w() == point_marker;
    };
    constexpr bool is_vector() const {
        return w() == vector_marker;
    }

    constexpr element_type dot_product(const Tuple& other) const {
        return std::inner_product(elements.cbegin(), elements.cend(), other.elements.cbegin(), 0.0);
    }

    template <size_t M = N>
    constexpr typename std::enable_if_t<M == 4, Tuple>
    cross_product(const Tuple& other) const {
        return {{
                y() * other.z() - z() * other.y(),
                z() * other.x() - x() * other.z(),
                x() * other.y() - y() * other.x(),
                vector_marker
        }};
    }

    // Can't do sqrt() as constexpr
    element_type magnitude() const {
        return std::sqrt(dot_product(*this));
    }

    Tuple normalize() const {
        return {*this / magnitude()};
    }
};

using Tuple4 = Tuple<double, 4>;

constexpr Tuple4 make_point(Tuple4::element_type x, Tuple4::element_type y, Tuple4::element_type z) {
    return {{x, y, z, Tuple4::point_marker}};
}

constexpr Tuple4 make_vector(Tuple4::element_type x, Tuple4::element_type y, Tuple4::element_type z) {
    return {{x, y, z, Tuple4::vector_marker}};
}

} // namespace raytracer

#endif // _TUPLE_H_
