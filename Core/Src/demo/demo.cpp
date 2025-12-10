#include "demo.h"
#include "main.h"

Demo::Demo(dd::led::IDisplay& display) : display_{display} {}

void Demo::Tick() {

    switch (state_) {
        case State::NO_INIT: {
            if (display_.GetState() == dd::led::IDisplay::State::INIT) {
                SetState(State::PLAYERS_RUNNING);
            }
            break;
        }
        case State::PLAYERS_RUNNING: {
            player_0_.Tick();
            player_1_.Tick();

            if ((player_0_.HeadPoint().x >= player_1_.HeadPoint().x) &&
                (player_0_.HeadPoint().y >= player_1_.HeadPoint().y)) {

                explosion_.Reset(player_0_.HeadPoint().x,
                                 player_0_.HeadPoint().y);
                SetState(State::EXPLOSION);
                break;
            }

            display_.Clear();
            player_0_.Draw();
            player_1_.Draw();
            display_.Draw();
            break;
        }
        case State::EXPLOSION: {
            display_.Clear();
            explosion_.Tick();
            display_.Draw();

            if (explosion_.IsDone()) {
                SetState(State::LOGO);
            }
            break;
        }
        case State::LOGO: {
            display_.Clear();
            logo_.Tick();
            display_.Draw();
            break;
        }
        default: {
            break;
        }
    }
}

void Demo::SetState(State state) {
    if (state_ == state) {
        return;
    }
    state_ = state;
    state_tick_ms_ = HAL_GetTick();

    switch (state_) {
        case State::NO_INIT: {
            break;
        }
        case State::PLAYERS_RUNNING: {
            auto color_0 = dd::led::Color24{.red = 64, .green = 64, .blue = 0};
            auto color_1 = dd::led::Color24{.red = 0, .green = 128, .blue = 0};

            player_0_.Reset(Player::Point{.x = 0, .y = 2, .color = color_0},
                            Player::Dir::FORWARD);

            player_1_.Reset(Player::Point{.x = display_.Width() - 1,
                                          .y = display_.Height() - 4,
                                          .color = color_1},
                            Player::Dir::BACKWARD);

            display_.Clear();
            break;
        }
        case State::EXPLOSION: {
            display_.Clear();
            display_.Draw();
            break;
        }
        case State::LOGO: {
            display_.Clear();
            display_.Draw();
            break;
        }
        default: {
            break;
        }
    }
}