#include "display.h"

namespace dd::led {

[[nodiscard]] IDisplay::State IDisplay::GetState() const {
    return state_;
}

}  // namespace dd::led