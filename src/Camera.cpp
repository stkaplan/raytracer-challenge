#include "Camera.h"

#include "Canvas.h"
#include "Ray.h"
#include "World.h"

#include <cmath>

namespace raytracer {

void Camera::calculate_pixel_size() {
    half_view = std::tan(field_of_view / 2.0);
    aspect_ratio = (double)horizontal_size / vertical_size;
    if (aspect_ratio >= 1.0) { // wider than tall
        half_width = half_view;
        half_height = half_view / aspect_ratio;
    } else {
        half_height = half_view;
        half_width = half_view * aspect_ratio;
    }

    pixel_size = half_width * 2.0 / horizontal_size;
}

Ray Camera::ray_for_pixel(double x, double y) const {
    double x_offset = (x + 0.5) * pixel_size;
    double y_offset = (y + 0.5) * pixel_size;

    double world_x = half_width - x_offset;
    double world_y = half_height - y_offset;

    auto pixel = transform_inverse * make_point(world_x, world_y, -1);
    auto origin = transform_inverse * make_point(0, 0, 0);
    auto direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

Canvas Camera::render(const World& world) const {
    Canvas image(horizontal_size, vertical_size);
    for (size_t y = 0; y < vertical_size-1; ++y) {
        for (size_t x = 0; x < horizontal_size-1; ++x) {
            auto ray = ray_for_pixel(x, y);
            auto color = world.color_at(ray);
            image.at(x, y) = color;
        }
    }

    return image;
}

} // namespace raytracer
