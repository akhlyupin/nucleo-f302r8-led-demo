#pragma once

#include <cinttypes>

namespace dd::game {

struct Snake {
    struct Position {
        std::int32_t x{0};
        std::int32_t y{0};
    };

    enum struct Direction {
        RIGHT,  //
        DOWN,   //
        LEFT,   //
        UP,     //
    };

    void Tick();

    [[nodiscard]] Position GetHeadPosition() const;
    [[nodiscard]] Direction GetDirection() const;
    void SetDirection(Direction dir);

    void IncrementLength();

   private:
    static constexpr std::size_t POSITION_LENGTH = 100;

    Position position_[POSITION_LENGTH]{};
    Direction dir_{Direction::RIGHT};
    std::size_t length_{3};

    std::uint32_t tick_ms_{0};

    [[nodiscard]] Position GetNextHeadPosition() const;
};

}  // namespace dd::game