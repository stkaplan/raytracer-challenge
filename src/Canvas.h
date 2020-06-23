#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "Color.h"

#include <stdexcept>
#include <vector>

namespace raytracer {

class Canvas {
private:
    size_t width;
    size_t height;
    std::vector<Color> pixels;

public:
    using iterator = decltype(pixels)::iterator;
    using const_iterator = decltype(pixels)::const_iterator;

    static constexpr int max_color = 255;

    Canvas(size_t width, size_t height)
        : width(width), height(height), pixels(height*width, make_color(0, 0, 0))
    { }

    size_t getWidth() const { return width; }
    size_t getHeight() const { return height; }
    Color& at(size_t x, size_t y) { return const_cast<Color&>(const_cast<const Canvas&>(*this).at(x, y)); }
    const Color& at(size_t x, size_t y) const {
        if (x >= width) throw std::out_of_range("Canvas::at(): invalid x value");
        if (y >= height) throw std::out_of_range("Canvas::at(): invalid y value");
        return pixels[x*height + y];
    }

    iterator begin() { return pixels.begin(); }
    iterator end() { return pixels.end(); }
    const_iterator begin() const { return pixels.begin(); }
    const_iterator end() const { return pixels.end(); }

    void writePPM(std::ostream& str) const;
};

} // namespace raytracer

#endif // _CANVAS_H_
