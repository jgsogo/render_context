#pragma once

#include "named_unit.hpp"

namespace math {

    namespace types {
        static const char pxSymbol[] = "px";

        template<typename T>
        using PixelsT = NamedUnitT<T, pxSymbol>;
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
