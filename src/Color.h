#ifndef _COLOR_H_
#define _COLOR_H_

#include "Tuple.h"

namespace raytracer {

class Color {
public:
    using elements_type = Tuple<double, 3>;
    using element_type = elements_type::element_type;

private:
    elements_type elements;

public:
    constexpr Color(const elements_type t)
        : elements(t) { }
    constexpr Color(element_type r, element_type g, element_type b)
        : elements({r, g, b}) { }

    constexpr element_type r() const { return elements[0]; }
    constexpr element_type g() const { return elements[1]; }
    constexpr element_type b() const { return elements[2]; }

    constexpr bool operator==(const Color& other) const {
        return elements == other.elements;
    }

    constexpr Color operator+(const Color& other) const {
        return Color(elements + other.elements);
    }
    constexpr Color operator-(const Color& other) const {
        return Color(elements - other.elements);
    }
    constexpr Color operator*(const element_type scalar) const {
        return Color(elements * scalar);
    }
    // Hadamard product (element-wise)
    constexpr Color operator*(const Color& other) const {
        return Color(r()*other.r(), g()*other.g(), b()*other.b());
    }

    friend std::ostream& operator<<(std::ostream& os, const Color& c) {
        os << "Color(" << c.r() << ", " << c.g() << ", " << c.b() << ")";
        return os;
    }

    static const Color BLACK;
    static const Color WHITE;
};

constexpr Color Color::BLACK(0, 0, 0);
constexpr Color Color::WHITE(1, 1, 1);

constexpr Color make_color(Color::element_type r, Color::element_type g, Color::element_type b) {
    return Color(r, g, b);
}

} // namespace raytracer

#endif // _COLOR_H_
