#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace sf_canvas
{

    struct Pixel
    {
        uint8_t Red, Green, Blue, Alpha;
    };

    static_assert(std::is_standard_layout_v<Pixel>);
    static_assert(sizeof(Pixel) == 4);
    static_assert(offsetof(Pixel, Red) == 0);
    static_assert(offsetof(Pixel, Green) == 1);
    static_assert(offsetof(Pixel, Blue) == 2);
    static_assert(offsetof(Pixel, Alpha) == 3);

}
