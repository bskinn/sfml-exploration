#include <cstdint>
#include <vector>

#include "canvas.hpp"

namespace sf_canvas
{

    Canvas::Canvas(uint16_t width, uint16_t height)
        : width_(width), height_(height), pixels_(width_ * height) {}

    Canvas::Canvas(uint16_t width, uint16_t height, Pixel px)
        : width_(width), height_(height)
    {
        std::vector<Pixel> init_px(width_ * height_, px);
        pixels_ = init_px;
    }

    uint8_t *Canvas::data()
    {
        return reinterpret_cast<uint8_t *>(pixels_.data());
    }

} // namespace sf_canvas
