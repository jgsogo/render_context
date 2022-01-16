#pragma once

#include "line_element.hpp"

namespace primitives {

    struct Line : LineElement {
        ImU32 color = IM_COL32_WHITE;
        math::Pixels thickness;
        Vector2Mm start;
        Vector2Mm end;

        [[nodiscard]] std::vector<Vector2Mm> getPolyline() const override;

        void doRender(RenderContext &render) const override;

        /*
        void doRender(Render &render) const override {
            render.drawLine(start, end, color, (float) thickness);
        }
         */
    };

}