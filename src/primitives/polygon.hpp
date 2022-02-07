#pragma once

#include "base_polygon.hpp"
#include "line_element.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList, const char *PixelsSymbol>
    struct ConvexPolygon : BasePolygon<Origin, TDrawList, PixelsSymbol> {
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::filled;
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::fillColor;
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::border;
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::borderColor;
        using BasePolygon<Origin, TDrawList, PixelsSymbol>::borderThickness;

        using RenderContext = typename LineElement<Origin, TDrawList, PixelsSymbol>::RenderContext;
        using Vector2Ori = typename RenderContext::Vector2Ori;

        std::vector<std::shared_ptr<LineElement<Origin, TDrawList, PixelsSymbol>>> lineElements;

        ~ConvexPolygon() = default;

        void doRender(RenderContext &render) const override {
            std::vector<Vector2Ori> points;
            for (auto &lineEl: lineElements) {
                auto ps = lineEl->getPolyline();
                std::copy(ps.begin(), ps.end(), std::back_inserter(points));
            }
            if (filled) {
                render.drawPolylineFilled(points, fillColor);
            }
            if (border) {
                render.drawPolyline(points, borderColor, borderThickness, ImDrawFlags_Closed);
            }
        }
    };

}
