#include "Environment.h"
#include "Projectile.h"

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
    Projectile proj(make_point(0, 1, 0), make_vector(1, 1, 0).normalize());
    Environment env(make_vector(0, -0.1, 0), make_vector(-0.01, 0, 0));

    int num_ticks = 0;
    while (proj.get_position().y() > 0.0) {
        std::cout << "Tick " << num_ticks << ": " << proj.get_position() << "\n";
        ++num_ticks;
        proj = tick(env, proj);
    }

    std::cout << "Final position: " << proj.get_position() << "\n";
}
