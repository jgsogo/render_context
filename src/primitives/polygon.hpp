#pragma once

#include "base_polygon.hpp"
#include "line_element.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList>
    struct ConvexPolygon : BasePolygon<Origin, TDrawList> {
        using BasePolygon<Origin, TDrawList>::filled;
        using BasePolygon<Origin, TDrawList>::fillColor;
        using BasePolygon<Origin, TDrawList>::border;
        using BasePolygon<Origin, TDrawList>::borderColor;
        using BasePolygon<Origin, TDrawList>::borderThickness;

        using RenderContext = typename LineElement<Origin, TDrawList>::RenderContext;
        using Vector2Ori = typename RenderContext::Vector2Ori;
        using OriginUnits = typename RenderContext::OriginUnits;


        std::vector<std::shared_ptr<LineElement<Origin, TDrawList>>> lineElements;

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
