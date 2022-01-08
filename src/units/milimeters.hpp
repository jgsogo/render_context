#pragma once

#include <Magnum/Math/Unit.h>

namespace math {
    namespace types {
        template<class T>
        class MilimetersT : public Magnum::Math::Unit<MilimetersT, T> {
        public:
            static constexpr char symbol[] = "mm";
        public:
            /** @brief Construct initialize to zero */
            constexpr /*implicit*/ MilimetersT() noexcept: Magnum::Math::Unit<MilimetersT, T>{Magnum::Math::ZeroInit} {}

            /** @brief Construct a zero */
            constexpr explicit MilimetersT(Magnum::Math::ZeroInitT) noexcept: Magnum::Math::Unit<MilimetersT, T>{Magnum::Math::ZeroInit} {}

            /** @brief Explicit constructor from unitless type */
            constexpr explicit MilimetersT(T value) noexcept: Magnum::Math::Unit<MilimetersT, T>(value) {}

            /** @brief Copy constructor */
            constexpr /*implicit*/ MilimetersT(Magnum::Math::Unit<MilimetersT, T> other) noexcept: Magnum::Math::Unit<MilimetersT, T>(other) {}

            /* Operators */
            friend std::ostream &operator<<(std::ostream &os, const MilimetersT &mms) {
                os << static_cast<T>(mms) << " " << symbol;
                return os;
            }
        };
    }

    using Milimeters = types::MilimetersT<double>;

    namespace units {
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

    }

}
