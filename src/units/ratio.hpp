#pragma once

#include <ostream>
#include <Magnum/Math/Unit.h>

namespace math {

    namespace types {
        namespace _impl {
            template<typename T>
            class RatioT : public Magnum::Math::Unit<RatioT, T> {
            public:
                constexpr explicit RatioT(T value) noexcept: Magnum::Math::Unit<RatioT, T>(value) {}

                constexpr explicit RatioT(Magnum::Math::IdentityInitT) noexcept: Magnum::Math::Unit<RatioT, T>(T{1}) {}
            };
        }

        template<template<typename> typename Origin,
                template<typename> typename Target,
                typename T>
        class RatioT : protected _impl::RatioT<T> {
            static_assert(!std::is_same_v<Origin<T>, Target<T>>, "A ratio should be always be between different types");
        public:
            RatioT(Origin<T> ori, Target<T> tgt) noexcept: _impl::RatioT<T>(static_cast<T>(tgt) / static_cast<T>(ori)) {}

            constexpr explicit RatioT(Magnum::Math::IdentityInitT) noexcept: _impl::RatioT<T>{Magnum::Math::IdentityInit} {}

            RatioT<Target, Origin, T> inverse() {
                return RatioT<Target, Origin, T>{Target{static_cast<T>(*this)}, Origin{T{1}}};
            }

            friend std::ostream &operator<<(std::ostream &os, const RatioT &mms) {
                os << static_cast<T>(mms) << " " << Target<T>::symbol << "/" << Origin<T>::symbol;
                return os;
            }

            friend Target<T> operator*(const RatioT<Origin, Target, T> &ratio, const Origin<T> &in) {
                return Target<T>{(T) ratio * (T) in};
            }

            friend Target<T> operator*(const Origin<T> &in, const RatioT<Origin, Target, T> &ratio) {
                return ratio * in;
            }

            friend Origin<T> operator*(const RatioT<Origin, Target, T> &ratio, const Target<T> &in) {
                return Origin<T>{(T) in / (T) ratio};
            }

            friend Origin<T> operator*(const Target<T> &in, const RatioT<Origin, Target, T> &ratio) {
                return ratio * in;
            }
        };

    }

    template<template<typename> typename Origin,
            template<typename> typename Target>
    types::RatioT<Origin, Target, double> ratio(Origin<double> ori, Target<double> tgt) {
        return types::RatioT<Origin, Target, double>(ori, tgt);
    }

}
