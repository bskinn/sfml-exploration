#include <cstdint>
#include <vector>

#include "canvas.hpp"

namespace sf_canvas
{

    Canvas::Canvas(uint16_t width, uint16_t height) : width_(width), height_(height)
    {
        std::vector<Pixel> pixels_(size_t(width_ * height_), Pixel{});
    }

} // namespace sf_canvas
