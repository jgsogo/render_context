#pragma once

#include <vector>
#include "primitive.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList>
    struct LineElement : Primitive<Origin, TDrawList> {
        [[nodiscard]] virtual std::vector<typename Primitive<Origin, TDrawList>::Vector2Ori> getPolyline() const = 0;
    };
}