#pragma once

#include <Magnum/Math/Angle.h>
#include "named_unit.hpp"

namespace math::units {
    constexpr Magnum::Math::Deg<double> operator ""_deg(long double d) {
        return Magnum::Math::Deg<double>{static_cast<double>(d)};
    }

    constexpr Magnum::Math::Deg<double> operator ""_deg(unsigned long long d) {
        return Magnum::Math::Deg<double>{static_cast<double>(d)};
    }
}
