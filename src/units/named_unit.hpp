#pragma once

#include <ostream>
#include <Magnum/Math/Unit.h>

namespace math::types {

    namespace _impl {

        template<class T>
        class NamedUnitT : public Magnum::Math::Unit<NamedUnitT, T> {
        public:
            /** @brief Construct initialize to zero */
            constexpr /*implicit*/ NamedUnitT() noexcept: Magnum::Math::Unit<NamedUnitT, T>{Magnum::Math::ZeroInit} {}

            /** @brief Construct a zero */
            constexpr explicit NamedUnitT(Magnum::Math::ZeroInitT) noexcept
                    : Magnum::Math::Unit<NamedUnitT, T>{Magnum::Math::ZeroInit} {}

            /** @brief Explicit constructor from unitless type */
            constexpr explicit NamedUnitT(T value) noexcept
                    : Magnum::Math::Unit<NamedUnitT, T>(value) {}

            /** @brief Copy constructor */
            constexpr /*implicit*/ NamedUnitT(Magnum::Math::Unit<NamedUnitT, T> other) noexcept
                    : Magnum::Math::Unit<NamedUnitT, T>(other) {}
        };
    }

    template<class T, const char *name>
    class NamedUnitT : public _impl::NamedUnitT<T> {
    public:
        constexpr static const char *symbol = name;
    public:
        /** @brief Construct initialize to zero */
        constexpr /*implicit*/ NamedUnitT() noexcept: _impl::NamedUnitT<T>{Magnum::Math::ZeroInit} {}

        /** @brief Construct a zero */
        constexpr explicit NamedUnitT(Magnum::Math::ZeroInitT) noexcept
                : _impl::NamedUnitT<T>{Magnum::Math::ZeroInit} {}

        /** @brief Explicit constructor from unitless type */
        constexpr explicit NamedUnitT(T value) noexcept
                : _impl::NamedUnitT<T>(value) {}

        /** @brief Copy constructor */
        //constexpr /*implicit*/ NamedUnitT(_impl::NamedUnitT<T> other) noexcept
        //        : _impl::NamedUnitT<T>(other) {}

        /** @brief Copy constructor */
        constexpr /*implicit*/ NamedUnitT(Magnum::Math::Unit<_impl::NamedUnitT, T> other) noexcept
                : _impl::NamedUnitT<T>(other) {}

        /* Operators */
        friend std::ostream &operator<<(std::ostream &os, const NamedUnitT &mms) {
            os << static_cast<T>(mms) << " " << symbol;
            return os;
        }
    };
}
