#pragma once

#include <Magnum/Math/Angle.h>

#include "milimeters.hpp"
#include "pixels.hpp"
#include "ratio.hpp"

namespace math {
    using Milimeters = types::MilimetersT<double>;
    using Pixels = types::PixelsT<double>;

    namespace units {
        /* Pixels */
        constexpr Pixels operator "" _px(long double d) {
            return Pixels{static_cast<double>(d)};
        }

        constexpr Pixels operator "" _px(unsigned long long d) {
            return Pixels{static_cast<double>(d)};
        }

        /* Milimeters */
        constexpr Milimeters operator "" _mm(long double d) {
            return Milimeters{static_cast<double>(d)};
        }

        constexpr Milimeters operator "" _mm(unsigned long long d) {
            return Milimeters{static_cast<double>(d)};
        }

        constexpr Milimeters operator "" _cm(long double d) {
            return Milimeters{static_cast<double>(d * 10)};
        }

        constexpr Milimeters operator "" _cm(unsigned long long d) {
            return Milimeters{static_cast<double>(d * 10)};
        }

        constexpr Milimeters operator "" _m(long double d) {
            return Milimeters{static_cast<double>(d * 1000)};
        }

        constexpr Milimeters operator "" _m(unsigned long long d) {
            return Milimeters{static_cast<double>(d * 1000)};
        }

        // Degrees
        constexpr Magnum::Math::Deg<double> operator ""_deg(long double d) {
            return Magnum::Math::Deg<double>{static_cast<double>(d)};
        }

        constexpr Magnum::Math::Deg<double> operator ""_deg(unsigned long long d) {
            return Magnum::Math::Deg<double>{static_cast<double>(d)};
        }
    }
}
