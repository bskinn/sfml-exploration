#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

#include <SFML/Graphics.hpp>

namespace sf_canvas
{

    struct Pixel
    {
        uint8_t Red = 0, Green = 0, Blue = 0, Alpha = 255;
    };

    static_assert(std::is_standard_layout_v<Pixel>);
    static_assert(sizeof(Pixel) == 4);
    static_assert(offsetof(Pixel, Red) == 0);
    static_assert(offsetof(Pixel, Green) == 1);
    static_assert(offsetof(Pixel, Blue) == 2);
    static_assert(offsetof(Pixel, Alpha) == 3);

    class Canvas
    {
    public:
        Canvas(uint16_t width, uint16_t height);

        uint8_t *data(void);

    private:
        uint16_t width_, height_;
        std::vector<Pixel> pixels_;
    };

} // namespace sf_canvas

namespace sf_canvas::helper
{
    sf::Color makeColorFromPixel(sf_canvas::Pixel px);
    uint32_t makeU32FromPixel(sf_canvas::Pixel px);
} // namespace sf_canvas::helper
