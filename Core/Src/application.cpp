#include <cinttypes>
#include <cstdio>
#include <cstring>
#include "led/ws2812.h"
#include "main.h"

extern "C" void app_init();
extern "C" void app_loop();
extern "C" void app_close();

static constexpr std::size_t STRIPE_SIZE = 120;
dd::led::ws2812::Stripe<STRIPE_SIZE> led_stripe{};

void app_init() {
    printf("\nHello WS2812 project!\n");

    HAL_Delay(200);
}

void app_loop() {
    static std::uint32_t tick_ms = 0;
    static std::uint32_t counter = 0;

    using Color = dd::led::Color24;
    static Color colors[STRIPE_SIZE] = {
        Color{.red = 128, .green = 0, .blue = 0},
        Color{.red = 64, .green = 64, .blue = 0},
        Color{.red = 0, .green = 128, .blue = 0},
        Color{.red = 0, .green = 64, .blue = 64},
        Color{.red = 0, .green = 0, .blue = 128},
        Color{.red = 64, .green = 0, .blue = 64}};

    if (HAL_GetTick() - tick_ms > 200) {
        tick_ms = HAL_GetTick();
        printf("counter: %lu\n", counter++);

        for (std::size_t i = 0; i < STRIPE_SIZE; i++) {
            led_stripe.Set(i, colors[(counter + i) % 6]);
        }
        led_stripe.Draw();
    }
}

void app_close() {}