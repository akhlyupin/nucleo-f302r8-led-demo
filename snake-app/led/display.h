#pragma once

#include "stripe.h"

namespace dd::led {

struct IDisplay {
    enum struct State {
        NO_INIT,
        INIT,
    };

    [[nodiscard]] State GetState() const;

    virtual void Clear() = 0;
    virtual void SetPixel(std::size_t x, std::size_t y, Color24 color) = 0;
    virtual void Draw() = 0;

    [[nodiscard]] virtual std::size_t Width() const = 0;
    [[nodiscard]] virtual std::size_t Height() const = 0;

   protected:
    State state_{State::NO_INIT};
};

template <std::size_t ROW_SIZE, std::size_t COLUMN_SIZE>
struct Display : public IDisplay {

    Display(IStripe& stripe) : stripe_{stripe} {
        if (ROW_SIZE * COLUMN_SIZE == stripe_.Size()) {
            state_ = State::INIT;
        }
    }

    [[nodiscard]] std::size_t Width() const override { return COLUMN_SIZE; }
    [[nodiscard]] std::size_t Height() const override { return ROW_SIZE; }

    void Clear() override {
        if (state_ == State::INIT) {
            stripe_.Clear();
        }
    }

    void SetPixel(std::size_t x, std::size_t y, Color24 color) override {

        if (state_ != State::INIT) {
            return;
        }

        if ((x >= COLUMN_SIZE) || (y >= ROW_SIZE)) {
            return;
        }

        std::size_t index;

        y = ROW_SIZE - 1 - y;

        if (y % 2 == 0) {
            index = y * COLUMN_SIZE + (COLUMN_SIZE - 1 - x);
        } else {
            index = y * COLUMN_SIZE + x;
        }

        stripe_.Set(index, color);
    }

    void Draw() override {
        if (state_ == State::INIT) {
            stripe_.Draw();
        }
    }

   private:
    IStripe& stripe_;
};

}  // namespace dd::led