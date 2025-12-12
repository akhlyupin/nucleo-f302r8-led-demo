#pragma once

#include <cinttypes>
#include "led/color.h"

namespace dd::led {

struct IStripe {
    virtual std::size_t Size() const = 0;
    virtual void Clear() = 0;
    virtual void Set(std::size_t index, Color24 color) = 0;
    virtual void Draw() = 0;
};

}  // namespace dd::led