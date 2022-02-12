#include "milimeters.hpp"

namespace math {

    template<>
    types::RatioT<units::m, units::mm, float> ratio<units::m, units::mm, float>() {
        return types::RatioT<units::m, units::mm, float>{Meters{1.f}, Milimeters{1000.f}};
    }

    template<>
    types::RatioT<units::mm, units::m, float> ratio<units::mm, units::m, float>() {
        return ratio<units::m, units::mm, float>().inverse();
    }

}
