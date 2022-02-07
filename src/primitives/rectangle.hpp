#pragma once

#include "base_polygon.hpp"


namespace primitives {

    template<const char *Origin, typename TDrawList, const char *PixelsSymbol>
    struct Rectangle : BasePolygon<Origin, TDrawList, PixelsSymbol> {
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::filled;
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::fillColor;
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::border;
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::borderColor;
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::borderThickness;

        using RenderContext = typename BasePolygon<Origin, TDrawList, PixelsSymbol>::RenderContext;
        using OriginUnits = typename RenderContext::OriginUnits;

        Magnum::Math::Range2D<OriginUnits> rect;

        void doRender(RenderContext &render) const override {
            if (filled) {
                render.drawRectangleFilled(rect, fillColor);
            }
            if (border) {
                render.drawRectangle(rect, borderColor, borderThickness);
            }
        }
    };
}
