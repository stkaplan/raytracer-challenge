#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Color.h"

#include <memory>
#include <ostream>

namespace raytracer {

class Pattern;
class PointLight;
class Shape;

class Material {
private:
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    std::shared_ptr<Pattern> pattern;

public:
    static constexpr double DEFAULT_AMBIENT = 0.1;
    static constexpr double DEFAULT_DIFFUSE = 0.9;
    static constexpr double DEFAULT_SPECULAR = 0.9;
    static constexpr double DEFAULT_SHININESS = 200.0;

    Material()
        : color(make_color(1, 1, 1)), ambient(DEFAULT_AMBIENT),
          diffuse(DEFAULT_DIFFUSE), specular(DEFAULT_SPECULAR),
          shininess(DEFAULT_SHININESS)
    { }

    Material(const Color& color, double ambient, double diffuse,
             double specular, double shininess,
             std::shared_ptr<Pattern> pattern = nullptr)
        : color(color), ambient(ambient), diffuse(diffuse),
          specular(specular), shininess(shininess), pattern(pattern)
    { }

    bool operator==(const Material& other) const = default;

    friend std::ostream& operator<<(std::ostream& os, const Material& m) {
        return os << "Material(" << m.color << ", "<< m.ambient << ", "
            << m.diffuse << ", " << m.specular << ", " << m.shininess << ")";
    }

    const Color& get_color() const { return color; }
    void set_color(const Color& c) { color = c; }

    double get_ambient() const { return ambient; }
    void set_ambient(double val) { ambient = val; }

    double get_diffuse() const { return diffuse; }
    void set_diffuse(double val) { diffuse = val; }

    double get_specular() const { return specular; }
    void set_specular(double val) { specular = val; }

    double get_shininess() const { return shininess; }
    void set_shininess(double val) { shininess = val; }

    std::shared_ptr<Pattern> get_pattern() const { return pattern; }
    void set_pattern(const std::shared_ptr<Pattern> p) { pattern = p; }

    Color lighting(const Shape& object,
                   const PointLight& light,
                   const Tuple4& position,
                   const Tuple4& eye_vector,
                   const Tuple4& normal_vector,
                   bool in_shadow) const;
};

} // namespace raytracer

#endif // _MATERIAL_H_
