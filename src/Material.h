#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Color.h"

#include "ostream"

namespace raytracer {

class PointLight;

class Material {
private:
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;

public:
    Material()
        : color(make_color(1, 1, 1)), ambient(0.1), diffuse(0.9),
          specular(0.9), shininess(200.0)
    { }

    Material(const Color& color, double ambient, double diffuse,
             double specular, double shininess)
        : color(color), ambient(ambient), diffuse(diffuse),
          specular(specular), shininess(shininess)
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

    Color lighting(const PointLight& light,
                   const Tuple4& position,
                   const Tuple4& eye_vector,
                   const Tuple4& normal_vector) const;
};

} // namespace raytracer

#endif // _MATERIAL_H_
