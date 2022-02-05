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

        /* Operators */
        friend std::ostream &operator<<(std::ostream &os, const NamedUnitT &mms) {
            os << static_cast<T>(mms) << " " << symbol;
            return os;
        }

        /* I cannot use operators from Magnum::Math::Unit because they return _impl::NamedUnitT class, they
         * are no longer of the same type as the one here, they have lost the symbol, so I can assign
         * different types: milimeters to pixels and so on,... */

        constexpr NamedUnitT<T, name> operator-() const {
            return NamedUnitT<T, name>{_impl::NamedUnitT<T>::operator-()};
        }

        NamedUnitT<T, name> &operator+=(NamedUnitT<T, name> other) {
            _impl::NamedUnitT<T>::operator+=(other);
            return *this;
        }

        constexpr NamedUnitT<T, name> operator+(NamedUnitT<T, name> other) const {
            return NamedUnitT<T, name>{_impl::NamedUnitT<T>::operator+(other)};
        }

        NamedUnitT<T, name> &operator-=(NamedUnitT<T, name> other) {
            _impl::NamedUnitT<T>::operator-=(other);
            return *this;
        }

        constexpr NamedUnitT<T, name> operator-(NamedUnitT<T, name> other) const {
            return NamedUnitT<T, name>{_impl::NamedUnitT<T>::operator-(other)};
        }

        friend constexpr NamedUnitT<T, name> operator*(T number, const NamedUnitT<T, name> &value) {
            return NamedUnitT<T, name>{static_cast<T>(value) * number};
        }

        friend constexpr NamedUnitT<T, name> operator*(const NamedUnitT<T, name> &value, T number) {
            return NamedUnitT<T, name>{static_cast<T>(value) * number};
        }

    protected:
        // We need this ctor for the operator overriding above
        constexpr /*implicit*/ NamedUnitT(Magnum::Math::Unit<_impl::NamedUnitT, T> other) noexcept
                : _impl::NamedUnitT<T>(other) {}
    };

}
