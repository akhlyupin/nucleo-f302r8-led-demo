#pragma once

#include "led/display.h"

struct Explosion {

    explicit Explosion(dd::led::IDisplay& display, std::size_t max_index);

    void Reset(std::size_t init_x, std::size_t init_y);
    void Tick();
    [[nodiscard]] bool IsDone() const;

   private:
    dd::led::IDisplay& display_;
    std::size_t max_index_;

    std::size_t index_{0};
    std::size_t init_x_{0};
    std::size_t init_y_{0};

    [[nodiscard]] std::size_t Distance(std::size_t x, std::size_t y) const;
};