#include "Material.h"

#include "Color.h"
#include "PointLight.h"

#include <cmath>

namespace raytracer {

Color Material::lighting(const PointLight& light,
                         const Tuple4& position,
                         const Tuple4& eye_vector,
                         const Tuple4& normal_vector) const
{
    auto effective_color = color * light.get_intensity();
    auto light_vector = (light.get_position() - position).normalize();
    auto ambient_color = effective_color * ambient;
    Color black(0, 0, 0);

    auto diffuse_color = black;
    auto specular_color = black;

    auto light_dot_normal = light_vector.dot_product(normal_vector);
    if (light_dot_normal > 0) {
        diffuse_color = effective_color * diffuse * light_dot_normal;

        auto reflect_vector = (-light_vector).reflect(normal_vector);
        auto reflect_dot_eye = reflect_vector.dot_product(eye_vector);
        if (reflect_dot_eye > 0) {
            auto factor = std::pow(reflect_dot_eye, shininess);
            specular_color = light.get_intensity() * specular * factor;
        }
    }

    return ambient_color + diffuse_color + specular_color;
}

} // namespace raytracer