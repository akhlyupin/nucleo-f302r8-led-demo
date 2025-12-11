#pragma once

#include <cinttypes>
#include "explosion.h"
#include "led/display.h"
#include "logo.h"
#include "player.h"

struct Demo {
    enum struct State {   //
        NO_INIT,          //
        PLAYERS_RUNNING,  //
        EXPLOSION,        //
        LOGO              //
    };

    explicit Demo(dd::led::IDisplay& display);

    void Tick();

   private:
    dd::led::IDisplay& display_;

    State state_{State::NO_INIT};
    std::uint32_t state_tick_ms_{0};

    Player player_0_{display_};
    Player player_1_{display_};
    Explosion explosion_{display_, 30};
    Logo logo_{display_};

    void SetState(State state);
};