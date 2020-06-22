#include "Canvas.h"

#include <algorithm>
#include <cmath>
#include <string_view>

namespace raytracer {

void Canvas::writePPM(std::ostream& str) const
{
    static constexpr std::string_view magic = "P3";
    static constexpr int max_text_width = 70;

    str << magic << "\n";
    str << width << " " << height << "\n";
    str << max_color << "\n";

    for (size_t y = 0; y < height; ++y) {
        int line_width = 0;

        for (size_t x = 0; x < width; ++x) {
            const auto& pixel = at(x, y);
            for (double channel : {pixel.r(), pixel.g(), pixel.b()}) {
                int channel_scaled = std::round(channel * max_color);
                channel_scaled = std::clamp(channel_scaled, 0, max_color);
                auto text = std::to_string(channel_scaled);

                // Wrap to next line if we can't fit.
                if (line_width + text.size() + 1 > max_text_width) {
                    str << "\n";
                    line_width = 0;
                }

                if (line_width != 0) str << " ";
                str << text;
                line_width += text.size() + 1;
            }
        }
        str << "\n";
    }
}

} // namespace raytracer
