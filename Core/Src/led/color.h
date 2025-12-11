#pragma once

#include <cinttypes>

namespace dd::led {

struct Color24 {
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;

    static Color24 Mix(std::uint8_t percent, Color24 c0, Color24 c1);
};

}  // namespace dd::led