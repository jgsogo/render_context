#pragma once

#include <Magnum/Math/Angle.h>
#include "named_unit.hpp"

namespace math::units {
    constexpr Magnum::Math::Deg<float> operator ""_deg(long double d) {
        return Magnum::Math::Deg<float>{static_cast<float>(d)};
    }

    constexpr Magnum::Math::Deg<float> operator ""_deg(unsigned long long d) {
        return Magnum::Math::Deg<float>{static_cast<float>(d)};
    }
}
