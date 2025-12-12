#include "color.h"

namespace dd::led {

std::uint8_t MixValue(std::uint8_t percent, uint32_t v0, uint32_t v1) {
    if (percent > 100) {
        percent = 100;
    }

    if (v0 > UINT8_MAX) {
        v0 = UINT8_MAX;
    }

    if (v1 > UINT8_MAX) {
        v1 = UINT8_MAX;
    }

    return static_cast<uint8_t>(v0 * percent / 100 +
                                v1 * (100 - percent) / 100);
}

Color24 Color24::Mix(std::uint8_t percent, Color24 c0, Color24 c1) {
    return Color24{.red = MixValue(percent, c0.red, c1.red),
                   .green = MixValue(percent, c0.green, c1.green),
                   .blue = MixValue(percent, c0.blue, c1.blue)};
}

}  // namespace dd::led