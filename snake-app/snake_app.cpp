#include <cinttypes>
#include <cstdio>
#include <cstring>
#include "led/display.h"
#include "led/ws2812.h"
#include "main.h"

extern "C" void app_init();
extern "C" void app_loop();
extern "C" void app_close();

static constexpr std::size_t STRIPE_SIZE = 120;
dd::led::ws2812::Stripe<STRIPE_SIZE> led_stripe{};
dd::led::Display<12, 10> display{led_stripe};

void app_init() {
    printf("\nHello WS2812 Snake project!\n");

    HAL_Delay(200);
}

void app_loop() {
    static std::uint32_t tick_ms = 0;

    if (HAL_GetTick() - tick_ms > 200) {
        tick_ms = HAL_GetTick();
    }
}

void app_close() {}