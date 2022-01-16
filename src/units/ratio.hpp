#pragma once

#include <ostream>
#include <Magnum/Math/Unit.h>
#include "named_unit.hpp"

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

        template<const char *symbolOrigin, const char *symbolTarget, typename T>
        class RatioT : protected _impl::RatioT<T> {
            static_assert(!std::is_same_v<NamedUnitT < T, symbolOrigin>, NamedUnitT < T, symbolTarget >> , "A ratio should always be between different types");
        public:
            using _impl::RatioT<T>::operator T;

            RatioT(NamedUnitT <T, symbolOrigin> ori, NamedUnitT <T, symbolTarget> tgt) noexcept: _impl::RatioT<T>(static_cast<T>(tgt) / static_cast<T>(ori)) {}

            constexpr explicit RatioT(Magnum::Math::IdentityInitT) noexcept: _impl::RatioT<T>{Magnum::Math::IdentityInit} {}

            RatioT<symbolTarget, symbolOrigin, T> inverse() {
                return RatioT<symbolTarget, symbolOrigin, T>{NamedUnitT<T, symbolTarget>{static_cast<T>(*this)}, NamedUnitT<T, symbolOrigin>{T{1}}};
            }

            explicit operator RatioT<symbolTarget, symbolOrigin, T>() const {
                return RatioT<symbolTarget, symbolOrigin, T>{NamedUnitT<T, symbolTarget>(static_cast<T>(*this)), NamedUnitT<T, symbolOrigin>{1.}};
            }

            friend std::ostream &operator<<(std::ostream &os, const RatioT &mms) {
                os << static_cast<T>(mms) << " " << symbolTarget << "/" << symbolOrigin;
                return os;
            }

            friend NamedUnitT <T, symbolTarget> operator*(const RatioT<symbolOrigin, symbolTarget, T> &ratio, const NamedUnitT <T, symbolOrigin> &in) {
                return NamedUnitT<T, symbolTarget>{static_cast<T>(ratio) * static_cast<T>(in)};
            }

            friend NamedUnitT <T, symbolTarget> operator*(const NamedUnitT <T, symbolOrigin> &in, const RatioT<symbolOrigin, symbolTarget, T> &ratio) {
                return ratio * in;
            }

            friend NamedUnitT <T, symbolOrigin> operator*(const RatioT<symbolOrigin, symbolTarget, T> &ratio, const NamedUnitT <T, symbolTarget> &in) {
                return NamedUnitT<T, symbolOrigin>{static_cast<T>(in) / static_cast<T>(ratio)};
            }

            friend NamedUnitT <T, symbolOrigin> operator*(const NamedUnitT <T, symbolTarget> &in, const RatioT<symbolOrigin, symbolTarget, T> &ratio) {
                return ratio * in;
            }
        };

    }

    /* Template declaration for fixed ratios between known units */
    template<const char *symbolOrigin, const char *symbolTarget, typename T>
    types::RatioT<symbolOrigin, symbolTarget, T> ratio();

    /* Creation of custom ratios */
    template<const char *symbolOrigin, const char *symbolTarget, typename T>
    types::RatioT<symbolOrigin, symbolTarget, T> ratio(types::NamedUnitT<T, symbolOrigin> ori, types::NamedUnitT<T, symbolTarget> tgt) {
        // TODO: Check if 'ratio()' exists, in that case: fail and force its usage
        return types::RatioT<symbolOrigin, symbolTarget, T>(ori, tgt);
    }

}
