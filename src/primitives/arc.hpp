#pragma once

#include "line_element.hpp"
#include "../units/degrees.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList>
    struct Arc : LineElement<Origin, TDrawList> {
        using RenderContext = typename LineElement<Origin, TDrawList>::RenderContext;
        using Vector2Ori = typename RenderContext::Vector2Ori;
        using OriginUnits = typename RenderContext::OriginUnits;

        // TODO: Is this a polyline?
        ImU32 color = IM_COL32_BLACK;
        math::Pixels thickness;
        Vector2Ori center;
        OriginUnits radius;
        Magnum::Deg start;
        Magnum::Deg end;
        bool dirNormal = true;

        [[nodiscard]] std::vector<Vector2Ori> getPolyline() const override {
            std::vector<Vector2Ori> points;
            if (dirNormal) {
                for (auto angle = start; angle < end; angle += Magnum::Deg{1.f}) {
                    points.emplace_back(Vector2Ori{
                            center.x() + radius * cos(angle),
                            center.y() + radius * sin(angle)
                    });
                }
            } else {
                for (auto angle = start; angle >= end; angle -= Magnum::Deg{1.f}) {
                    points.emplace_back(Vector2Ori{
                            center.x() + radius * cos(angle),
                            center.y() + radius * sin(angle)
                    });
                }
            }
            // And the end-point
            points.emplace_back(Vector2Ori{
                    center.x() + radius * cos(end),
                    center.y() + radius * sin(end)
            });
            return points;
        }

        void doRender(RenderContext &render) const override {
            auto points = getPolyline();
            render.drawPolyline(points, color, thickness, 0);
        }

    };

}
