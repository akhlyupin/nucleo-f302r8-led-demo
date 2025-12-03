#include <cinttypes>
#include <cstdio>
#include "main.h"

extern "C" void app_init();
extern "C" void app_loop();
extern "C" void app_close();

void app_init() {
    printf("\nHello WS2812 project!\n");
}

void app_loop() {
    static std::uint32_t tick_ms = 0;
    static std::uint32_t counter = 0;

    if (HAL_GetTick() - tick_ms > 1000) {
        tick_ms = HAL_GetTick();

        printf("counter: %lu\n", counter++);
    }
}

void app_close() {}