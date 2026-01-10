#include <cstdint>
#include <SFML/Graphics.hpp>

#include "canvas.hpp"

using sf::Color;
using sf_canvas::Pixel;

namespace sf_canvas::helper {
    Color makeColorFromPixel(Pixel px) {
        return Color(px.Red, px.Green, px.Blue, px.Alpha);
    }

    uint32_t makeU32FromPixel(Pixel px) {
        return ((uint32_t)px.Red << 24)
                | ((uint32_t)px.Green << 16)
                | ((uint32_t)px.Blue << 8)
                | (uint32_t)px.Alpha;
    }

}
