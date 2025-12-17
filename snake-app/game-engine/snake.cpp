#include "snake.h"
#include "main.h"

namespace dd::game {

void Snake::Tick() {
    if (HAL_GetTick() - tick_ms_ < 200) {
        return;
    }
    tick_ms_ = HAL_GetTick();

    for (std::size_t i = length_; i > 1; i--) {
        position_[i - 1] = position_[i - 2];
    }

    position_[0] = GetNextHeadPosition();
}

[[nodiscard]] Snake::Position Snake::GetHeadPosition() const {
    return position_[0];
}

[[nodiscard]] Snake::Direction Snake::GetDirection() const {
    return dir_;
}

void Snake::SetDirection(Direction dir) {
    dir_ = dir;
}

void Snake::IncrementLength() {
    if (length_ >= POSITION_LENGTH) {
        return;
    }
    length_++;

    for (std::size_t i = length_; i > 1; i--) {
        position_[i - 1] = position_[i - 2];
    }

    position_[0] = GetNextHeadPosition();
}

[[nodiscard]] Snake::Position Snake::GetNextHeadPosition() const {
    auto pos = GetHeadPosition();

    switch (GetDirection()) {
        case Direction::RIGHT: {
            return Position{.x = pos.x + 1, .y = pos.y};
        }
        case Direction::DOWN: {
            return Position{.x = pos.x, .y = pos.y - 1};
        }
        case Direction::LEFT: {
            return Position{.x = pos.x - 1, .y = pos.y};
        }
        case Direction::UP: {
            return Position{.x = pos.x, .y = pos.y + 1};
        }
        default: {
            break;
        }
    }

    return pos;
}

}  // namespace dd::game