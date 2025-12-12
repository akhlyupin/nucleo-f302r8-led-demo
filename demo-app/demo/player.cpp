#include "player.h"

Player::Player(dd::led::IDisplay& display) : display_{display} {}

void Player::Reset(Point point, Dir dir) {
    dir_ = dir;
    point_[0] = point;

    auto color_1 =
        dd::led::Color24{.red = static_cast<uint8_t>(point.color.red / 20),
                         .green = static_cast<uint8_t>(point.color.green / 20),
                         .blue = static_cast<uint8_t>(point.color.blue / 20)};
    point_[1] = Point{.x = SIZE_MAX, .y = SIZE_MAX, .color = color_1};

    auto color_2 =
        dd::led::Color24{.red = static_cast<uint8_t>(point.color.red / 60),
                         .green = static_cast<uint8_t>(point.color.green / 60),
                         .blue = static_cast<uint8_t>(point.color.blue / 60)};
    point_[2] = Point{.x = SIZE_MAX, .y = SIZE_MAX, .color = color_2};
}

void Player::Tick() {
    point_[2].x = point_[1].x;
    point_[2].y = point_[1].y;
    point_[1].x = point_[0].x;
    point_[1].y = point_[0].y;

    if (dir_ == Dir::FORWARD) {
        if (point_[0].x == display_.Width() - 1) {
            point_[0].x = 0;
            point_[0].y++;
        } else {
            point_[0].x++;
        }

    } else {
        if (point_[0].x == 0) {
            point_[0].x = display_.Width() - 1;
            point_[0].y--;
        } else {
            point_[0].x--;
        }
    }
}

void Player::Draw() {
    display_.SetPixel(point_[0].x, point_[0].y, point_[0].color);

    if ((point_[1].x != SIZE_MAX) && (point_[1].y != SIZE_MAX)) {
        display_.SetPixel(point_[1].x, point_[1].y, point_[1].color);
    }

    if ((point_[2].x != SIZE_MAX) && (point_[2].y != SIZE_MAX)) {
        display_.SetPixel(point_[2].x, point_[2].y, point_[2].color);
    }
}

[[nodiscard]] const Player::Point& Player::HeadPoint() const {
    return point_[0];
}