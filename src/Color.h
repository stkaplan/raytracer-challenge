#ifndef _COLOR_H_
#define _COLOR_H_

#include "Tuple.h"

namespace raytracer {

class Color {
public:
    using element_type = Tuple::element_type;

private:
    Tuple elements;

public:
    constexpr Color(const Tuple& t)
        : elements(t) { }
    constexpr Color(element_type r, element_type g, element_type b)
        : elements(Tuple(r, g, b, 0)) { }

    constexpr element_type r() const { return elements.x(); }
    constexpr element_type g() const { return elements.y(); }
    constexpr element_type b() const { return elements.z(); }

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
};

constexpr Color make_color(Color::element_type r, Color::element_type g, Color::element_type b) {
    return Color(r, g, b);
}

} // namespace raytracer

#endif // _COLOR_H_
