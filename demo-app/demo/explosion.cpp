#include "explosion.h"
#include <cmath>
#include <cstdio>

Explosion::Explosion(dd::led::IDisplay& display, std::size_t max_index)
    : display_{display}, max_index_{max_index} {}

void Explosion::Reset(std::size_t init_x, std::size_t init_y) {
    init_x_ = init_x;
    init_y_ = init_y;
    index_ = 0;
}

std::size_t Explosion::Distance(std::size_t x, std::size_t y) const {
    int init_x = static_cast<int>(init_x_);
    int init_y = static_cast<int>(init_y_);
    int ix = static_cast<int>(x);
    int iy = static_cast<int>(y);

    int32_t dist = sqrt(abs(ix - init_x) * abs(ix - init_x) +
                        abs(iy - init_y) * abs(iy - init_y));

    return static_cast<std::size_t>(dist);
}

void Explosion::Tick() {
    if (index_ > max_index_) {
        return;
    }

    for (std::size_t y = 0; y < display_.Height(); y++) {
        for (std::size_t x = 0; x < display_.Width(); x++) {
            auto dist = Distance(x, y);

            if (dist > index_) {
                continue;
            }

            std::size_t front_dist = index_ - dist;

            using Color24 = dd::led::Color24;
            Color24 red_color{.red = 128, .green = 0, .blue = 0};
            Color24 yellow_color{.red = 128, .green = 64, .blue = 0};
            Color24 empty_color{.red = 0, .green = 0, .blue = 0};
            Color24 out_color{.red = 0, .green = 0, .blue = 0};

            if (front_dist < 4) {
                out_color = Color24::Mix((4 - front_dist) * 100 / 4,  //
                                         red_color,                   //
                                         yellow_color);               //
            } else if (front_dist < 6) {
                front_dist -= 4;
                out_color = Color24::Mix((2 - front_dist) * 100 / 2,  //
                                         yellow_color,                //
                                         empty_color);                //
            }

            display_.SetPixel(x, y, out_color);
        }
    }

    index_++;
}

[[nodiscard]] bool Explosion::IsDone() const {
    return index_ > 14;
}