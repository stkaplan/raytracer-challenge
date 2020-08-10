#include "Environment.h"
#include "Projectile.h"

#include <Canvas.h>

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace raytracer;

Projectile tick(const Environment& env, const Projectile& proj) {
    return Projectile(
        proj.get_position() + proj.get_velocity(),
        proj.get_velocity() + env.get_gravity() + env.get_wind()
    );
}

int main()
{
    Projectile proj(make_point(0, 1, 0), make_vector(1, 1.8, 0).normalize() * 11.25);
    Environment env(make_vector(0, -0.1, 0), make_vector(-0.01, 0, 0));
    Canvas canvas(900, 550);

    Color red(1, 0, 0);

    int num_ticks = 0;
    while (proj.get_position().y() > 0.0) {
        std::cout << "Tick " << num_ticks << ": " << proj.get_position() << "\n";

        int x = std::round(proj.get_position().x());
        int y = std::round(proj.get_position().y());
        assert(x >= 0 && x < canvas.get_width());
        assert(y >= 0 && y < canvas.get_height());
        canvas.at(x, canvas.get_height() - y) = red;

        ++num_ticks;
        proj = tick(env, proj);
    }

    std::cout << "Final position: " << proj.get_position() << "\n";

    std::ofstream image("image.ppm");
    canvas.writePPM(image);
}
