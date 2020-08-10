#include <Canvas.h>
#include <Transformations.h>

#include <fstream>

using namespace raytracer;

void draw(Canvas& canvas, const Tuple4& point, const Color& color)
{
    auto translate_to_center = translation(canvas.get_width()/2, canvas.get_height()/2, 0);
    auto translated_point = translate_to_center * point;
    canvas.at(translated_point.x(), translated_point.y()) = color;
}

int main()
{
    auto canvas_size = 200;
    auto border = 20;
    double hour_hand_size = canvas_size/2 - border;

    auto white = make_color(1, 1, 1);

    Canvas canvas(canvas_size, canvas_size);

    auto scale_hour = scale(hour_hand_size, hour_hand_size, 0);
    auto rotate_hour = rotation<Dimension::Z>(M_PI/6);

    auto origin = make_point(0, 0, 0);
    draw(canvas, origin, white);

    // Draw points at each hour mark.
    auto mark = scale_hour * make_point(0, -1, 0);
    for (int i = 0; i < 12; ++i) {
        mark = rotate_hour * mark;
        draw(canvas, mark, white);
    }

    std::ofstream image("image.ppm");
    canvas.writePPM(image);
}
