#pragma once

#include <cinttypes>
#include "led/color.h"
#include "led/display.h"

struct Player {
    struct Point {
        std::size_t x;
        std::size_t y;
        dd::led::Color24 color;
    };

    enum struct Dir {
        FORWARD,  //
        BACKWARD  //
    };

    explicit Player(dd::led::IDisplay& display);

    void Reset(Point point, Dir dir);
    void Tick();
    void Draw();

    [[nodiscard]] const Point& HeadPoint() const;

   private:
    dd::led::IDisplay& display_;

    Point point_[3]{};
    Dir dir_{Dir::FORWARD};
};