#pragma once

#include "line_element.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList>
    struct Line : LineElement<Origin, TDrawList> {
        ImU32 color = IM_COL32_WHITE;
        math::Pixels thickness;
        typename LineElement<Origin, TDrawList>::Vector2Ori start;
        typename LineElement<Origin, TDrawList>::Vector2Ori end;

        [[nodiscard]] std::vector<typename LineElement<Origin, TDrawList>::Vector2Ori> getPolyline() const override {
            return {start, end};
        }

        void doRender(typename LineElement<Origin, TDrawList>::RenderContext &render) const override {
            render.drawLine(start, end, color, thickness);
        }
    };

}