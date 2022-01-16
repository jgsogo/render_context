#pragma once

#include "named_unit.hpp"

namespace math {

    namespace types {
        static const char mmSymbol[] = "mm";

        template<typename T>
        using MilimetersT = NamedUnitT<T, mmSymbol>;
    }

    using Milimeters = types::MilimetersT<float>;

    namespace units {
        constexpr Milimeters operator "" _mm(long double d) {
            return Milimeters{static_cast<float>(d)};
        }

        constexpr Milimeters operator "" _mm(unsigned long long d) {
            return Milimeters{static_cast<float>(d)};
        }

        constexpr Milimeters operator "" _cm(long double d) {
            return Milimeters{static_cast<float>(d * 10)};
        }

        constexpr Milimeters operator "" _cm(unsigned long long d) {
            return Milimeters{static_cast<float>(d * 10)};
        }

        constexpr Milimeters operator "" _m(long double d) {
            return Milimeters{static_cast<float>(d * 1000)};
        }

        constexpr Milimeters operator "" _m(unsigned long long d) {
            return Milimeters{static_cast<float>(d * 1000)};
        }

        /*
        // Degrees
        constexpr Magnum::Math::Deg<double> operator ""_deg(long double d) {
            return Magnum::Math::Deg<double>{static_cast<double>(d)};
        }

        constexpr Magnum::Math::Deg<double> operator ""_deg(unsigned long long d) {
            return Magnum::Math::Deg<double>{static_cast<double>(d)};
        }
         */
    }
}
