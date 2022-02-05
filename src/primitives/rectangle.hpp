#pragma once

#include "base_polygon.hpp"


namespace primitives {

    template<const char *Origin, typename TDrawList>
    struct Rectangle : BasePolygon<Origin, TDrawList> {
        using BasePolygon<Origin, TDrawList>::filled;
        using BasePolygon<Origin, TDrawList>::fillColor;
        using BasePolygon<Origin, TDrawList>::border;
        using BasePolygon<Origin, TDrawList>::borderColor;
        using BasePolygon<Origin, TDrawList>::borderThickness;

        using RenderContext = typename BasePolygon<Origin, TDrawList>::RenderContext;
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
