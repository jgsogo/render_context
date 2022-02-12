#pragma once

#include "named_unit.hpp"

namespace math {

    namespace units {
        inline constexpr const char px[] = "px";
    }

    namespace types {
        template<typename T>
        using PixelsT = NamedUnitT<T, units::px>;
    }

    using Pixels = types::PixelsT<float>;

    namespace units {
        constexpr Pixels operator "" _px(long double d) {
            return Pixels{static_cast<float>(d)};
        }

        constexpr Pixels operator "" _px(unsigned long long d) {
            return Pixels{static_cast<float>(d)};
        }
    }
}
