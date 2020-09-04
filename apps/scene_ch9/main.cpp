#include <Camera.h>
#include <Canvas.h>
#include <Material.h>
#include <Plane.h>
#include <PointLight.h>
#include <Sphere.h>
#include <Transformations.h>
#include <World.h>

#include <cmath>
#include <fstream>
#include <memory>

using namespace raytracer;

int main()
{
    World world;
    Material floor_material(make_color(1.0, 0.9, 0.9),
            Material::DEFAULT_AMBIENT, Material::DEFAULT_DIFFUSE, 0.0,
            Material::DEFAULT_SHININESS);

    auto floor = std::make_unique<Plane>();
    floor->set_material(floor_material);
    world.add_object(std::move(floor));

    auto middle = std::make_unique<Sphere>();
    middle->set_transform(translation(-0.5, 1, 0.5));
    middle->set_material(Material(make_color(0.1, 1.0, 0.5),
            Material::DEFAULT_AMBIENT, 0.7, 0.3, Material::DEFAULT_SHININESS));
    world.add_object(std::move(middle));

    auto right = std::make_unique<Sphere>();
    right->set_transform(translation(1.5, 0.5, -0.5) * scale(0.5, 0.5, 0.5));
    right->set_material(Material(make_color(0.5, 1, 0.1),
            Material::DEFAULT_AMBIENT, 0.7, 0.3, Material::DEFAULT_SHININESS));
    world.add_object(std::move(right));

    auto left = std::make_unique<Sphere>();
    left->set_transform(translation(-1.5, 0.33, -0.75) * scale(0.33, 0.33, 0.33));
    left->set_material(Material(make_color(1.0, 0.8, 0.1),
            Material::DEFAULT_AMBIENT, 0.7, 0.3, Material::DEFAULT_SHININESS));
    world.add_object(std::move(left));

    PointLight light(make_point(-10, 10, -10), make_color(1, 1, 1));
    world.set_light(light);

    Camera camera(1000, 500, M_PI/3.0, view_transform(make_point(0, 1.5, -5), make_point(0, 1, 0), make_vector(0, 1, 0)));
    auto canvas = camera.render(world);
    std::ofstream image("image.ppm");
    canvas.writePPM(image);
}
