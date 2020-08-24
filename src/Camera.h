#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Canvas.h"
#include "Ray.h"
#include "Transformations.h"

#include <cassert>

namespace raytracer {

class World;

class Camera {
private:
    size_t horizontal_size;
    size_t vertical_size;
    double field_of_view;
    TransformationMatrix transform;
    
    // Cached values used for later computations.
    void calculate_pixel_size();
    double half_view;
    double aspect_ratio;
    double half_width;
    double half_height;
    double pixel_size;
    TransformationMatrix transform_inverse;

public:
    Camera(size_t hsize, size_t vsize, double fov, TransformationMatrix transform = make_identity<double, 4>())
        : horizontal_size(hsize), vertical_size(vsize), field_of_view(fov), transform(transform)
    { 
        calculate_pixel_size();
        auto inv = transform.inverse();
        assert(inv.has_value());
        transform_inverse = *inv;
    }

    auto get_horizontal_size() const { return horizontal_size; }
    auto get_vertical_size() const { return vertical_size; }
    auto get_field_of_view() const { return field_of_view; }
    const auto& get_transform() const { return transform; }
    auto get_pixel_size() const { return pixel_size; }

    Ray ray_for_pixel(double x, double y) const;
    Canvas render(const World& world) const;
};

} // namespace raytracer

#endif // _CAMERA_H_
