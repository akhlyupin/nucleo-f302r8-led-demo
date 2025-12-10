#include "logo.h"
#include "main.h"

Logo::Logo(dd::led::IDisplay& display) : display_{display} {}

void Logo::Tick() {
    static constexpr Color red_color{.red = 255, .green = 0, .blue = 0};
    static constexpr Color yellow_color{.red = 255, .green = 128, .blue = 0};

    SetUndeline();

    static constexpr std::size_t OPACITY_SIZE = 10;
    static std::uint32_t opacity[OPACITY_SIZE] = {0,  1,  2,  5,  10,
                                                  20, 40, 60, 80, 100};

    PutD(1, 2, SetOpacity(red_color, opacity[index_]));
    PutD(6, 2, SetOpacity(yellow_color, opacity[index_]));

    index_ = (direction_) ? index_ + 1 : index_ - 1;
    if (index_ >= OPACITY_SIZE) {
        direction_ = !direction_;
        index_ = (direction_) ? index_ + 2 : index_ - 2;
    }
}

void Logo::PutD(std::size_t x, std::size_t y, dd::led::Color24 color) {
    display_.SetPixel(x, y, color);
    display_.SetPixel(x, y + 1, color);
    display_.SetPixel(x, y + 2, color);
    display_.SetPixel(x, y + 3, color);
    display_.SetPixel(x, y + 4, color);
    display_.SetPixel(x, y + 5, color);
    display_.SetPixel(x, y + 6, color);

    display_.SetPixel(x + 1, y, color);
    display_.SetPixel(x + 1, y + 6, color);

    display_.SetPixel(x + 2, y + 1, color);
    display_.SetPixel(x + 2, y + 5, color);

    display_.SetPixel(x + 3, y + 2, color);
    display_.SetPixel(x + 3, y + 3, color);
    display_.SetPixel(x + 3, y + 4, color);
}

void Logo::SetUndeline() {
    Color color{.red = underline_index_,
                      .green = (underline_index_ > 3) ? (uint8_t)1 : (uint8_t)0,
                      .blue = 0};

    for (std::size_t x = 0; x < display_.Width(); x++) {
        display_.SetPixel(x, 0, color);
        display_.SetPixel(x, display_.Height() - 2, color);
    }

    underline_index_++;
    if (underline_index_ > 6) {
        underline_index_ = 6;
    }
}

[[nodiscard]] Logo::Color Logo::SetOpacity(Color color,
                                           std::uint32_t opacity) const {
    if (opacity > 100) {
        opacity = 100;
    }

    color.red = static_cast<std::uint8_t>(
        static_cast<std::uint32_t>(color.red) * opacity / 100);
    color.green = static_cast<std::uint8_t>(
        static_cast<std::uint32_t>(color.green) * opacity / 100);
    color.blue = static_cast<std::uint8_t>(
        static_cast<std::uint32_t>(color.blue) * opacity / 100);

    return color;
}