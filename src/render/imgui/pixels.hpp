#pragma once

#include "../../units/named_unit.hpp"

namespace render::imgui {
    namespace units {
        inline constexpr const char impx[] = "impx";
    }

    using Pixels = math::types::NamedUnitT<float, units::impx>;

    namespace units {
        constexpr Pixels operator "" _impx(long double d) {
            return Pixels{static_cast<float>(d)};
        }

        constexpr Pixels operator "" _impx(unsigned long long d) {
            return Pixels{static_cast<float>(d)};
        }
    }
}
