#pragma once

#include "ratio.hpp"
#include "named_unit.hpp"

namespace math {

    namespace units {
        static const char mm[] = "mm";
        static const char m[] = "m";
    }

    namespace types {
        template<typename T> using MilimetersT = NamedUnitT<T, units::mm>;
        template<typename T> using MetersT = NamedUnitT<T, units::m>;
    }

    using Milimeters = types::MilimetersT<float>;
    using Meters = types::MetersT<float>;

    // Literal strings
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
    }

    // Some known ratios
    template<>
    types::RatioT<units::m, units::mm, float> ratio<units::m, units::mm, float>() {
        return types::RatioT<units::m, units::mm, float>{Meters{1.f}, Milimeters{1000.f}};
    }

    template<>
    types::RatioT<units::mm, units::m, float> ratio<units::mm, units::m, float>() {
        return ratio<units::m, units::mm, float>().inverse();
    }
}
