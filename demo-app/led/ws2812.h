#pragma once

#include <cinttypes>
#include <cstdio>
#include "led/color.h"
#include "led/stripe.h"
#include "main.h"

namespace dd::led::ws2812 {

template <std::size_t SIZE>
struct Stripe : public IStripe {

    Stripe() {
        memset(data_, 0, sizeof(data_));
        Clear();
    }

    std::size_t Size() const override { return SIZE; }

    void Clear() override {
        for (std::size_t i = 0; i < SIZE * BITS_PER_LED; i++) {
            data_[i] = 30;
        }
    }

    void Set(std::size_t index, Color24 color) override {
        if (index >= SIZE) {
            return;
        }

        for (std::uint8_t i = 0; i < 8; i++) {
            data_[index * BITS_PER_LED + i] = (color.green & 0x80) ? 60 : 30;
            color.green <<= 1;

            data_[index * BITS_PER_LED + i + 8] = (color.red & 0x80) ? 60 : 30;
            color.red <<= 1;

            data_[index * BITS_PER_LED + i + 16] =
                (color.blue & 0x80) ? 60 : 30;
            color.blue <<= 1;
        }
    }

    void Draw() override {
        TIM1->CNT = 0;

        if (HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)data_,
                                  DATA_SIZE) != HAL_OK) {
            printf("E PWM Start error!\n");
        }

        while (HAL_TIM_OC_GetState(&htim1) != HAL_TIM_STATE_READY) {}
    }

   private:
    static constexpr std::size_t RESET_SIZE = 250;
    static constexpr std::size_t BITS_PER_LED = 24;
    static constexpr std::size_t DATA_SIZE = SIZE * BITS_PER_LED + RESET_SIZE;

    std::uint8_t data_[DATA_SIZE]{};
};

}  // namespace dd::led::ws2812