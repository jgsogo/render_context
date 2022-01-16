#pragma once

#include <ostream>
#include <Magnum/Math/Unit.h>

namespace math::types {
    template<class T>
    class PixelsT : public Magnum::Math::Unit<PixelsT, T> {
    public:
        static constexpr char symbol[] = "px";
    public:
        /** @brief Construct initialize to zero */
        constexpr /*implicit*/ PixelsT() noexcept: Magnum::Math::Unit<PixelsT, T>{Magnum::Math::ZeroInit} {}

        /** @brief Construct a zero */
        constexpr explicit PixelsT(Magnum::Math::ZeroInitT) noexcept: Magnum::Math::Unit<PixelsT, T>{Magnum::Math::ZeroInit} {}

        /** @brief Explicit constructor from unitless type */
        constexpr explicit PixelsT(T value) noexcept: Magnum::Math::Unit<PixelsT, T>(value) {}

        /** @brief Copy constructor */
        constexpr /*implicit*/ PixelsT(Magnum::Math::Unit<PixelsT, T> other) noexcept: Magnum::Math::Unit<PixelsT, T>(other) {}

        /* Operators */
        friend std::ostream &operator<<(std::ostream &os, const PixelsT &mms) {
            os << static_cast<T>(mms) << " " << symbol;
            return os;
        }
    };
}
