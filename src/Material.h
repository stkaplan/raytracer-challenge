#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Color.h"


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

    bool operator==(const Material& other) const {
        return color == other.color
            && ambient == other.ambient
            && diffuse == other.diffuse
            && specular == other.specular
            && shininess == other.shininess;
    }

    const Color& get_color() const { return color; }
    double get_ambient() const { return ambient; }
    double get_diffuse() const { return diffuse; }
    double get_specular() const { return specular; }
    double get_shininess() const { return shininess; }

    Color lighting(const PointLight& light,
                   const Tuple4& position,
                   const Tuple4& eye_vector,
                   const Tuple4& normal_vector) const;
};

} // namespace raytracer

#endif // _MATERIAL_H_
