#pragma once

#include <cinttypes>
#include "led/display.h"

struct Logo {

    explicit Logo(dd::led::IDisplay& display);

    void Tick();

   private:
    using Color = dd::led::Color24;

    dd::led::IDisplay& display_;
    bool direction_{true};
    std::size_t index_{0};
    std::uint8_t underline_index_{0};

    void PutD(std::size_t x, std::size_t y, dd::led::Color24 color);
    void SetUndeline();
    [[nodiscard]] Color SetOpacity(Color color, std::uint32_t opacity) const;
};