#pragma once

#include <vector>
#include "primitive.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList, const char *PixelsSymbol>
    struct LineElement : Primitive<Origin, TDrawList, PixelsSymbol> {
        [[nodiscard]] virtual std::vector<typename Primitive<Origin, TDrawList, PixelsSymbol>::Vector2Ori> getPolyline() const = 0;
    };
}