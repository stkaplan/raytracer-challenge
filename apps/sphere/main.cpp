#include <Canvas.h>
#include <Ray.h>
#include <Sphere.h>

#include <fstream>

using namespace raytracer;

int main()
{
    size_t canvas_size = 200;
    Canvas canvas(canvas_size, canvas_size);

    auto red = make_color(1, 0, 0);

    auto ray_origin = make_point(0, 0, -5);
    double wall_z = 10.0;
    double wall_size = 7.0;
    double half = wall_size / 2.0;

    Sphere sphere;

    double pixel_size = wall_size / canvas_size;

    for (size_t y = 0; y < canvas_size; ++y) {
        // top = +half, bottom = -half
        double world_y = half - (pixel_size * y);

        for (size_t x = 0; x < canvas_size; ++x) {
            // left = -half, right = +half
            double world_x = -half + (pixel_size * x);
            auto position = make_point(world_x, world_y, wall_z);

            Ray ray(ray_origin, (position - ray_origin).normalize());
            auto intersections = sphere.intersect(ray);
            auto hit = find_hit(intersections);
            if (hit.has_value()) {
                canvas.at(x, y) = red;
            }
        }
    }

    std::ofstream image("image.ppm");
    canvas.writePPM(image);
}
