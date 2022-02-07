#pragma once

#include "primitive.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList, const char *PixelsSymbol>
    struct BasePolygon : Primitive<Origin, TDrawList, PixelsSymbol> {
        using RenderContext = typename Primitive<Origin, TDrawList, PixelsSymbol>::RenderContext;
        using PixelUnits = typename RenderContext::PixelUnits;

        bool filled = true;
        ImU32 fillColor = IM_COL32_BLACK;
        bool border = true;
        ImU32 borderColor = IM_COL32(255, 0, 0, 255);
        PixelUnits borderThickness{1.f};
    };

}