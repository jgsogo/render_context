#pragma once

#include "line_element.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList, const char *PixelsSymbol>
    struct Line : LineElement<Origin, TDrawList, PixelsSymbol> {
        using RenderContext = typename LineElement<Origin, TDrawList, PixelsSymbol>::RenderContext;
        using PixelUnits = typename RenderContext::PixelUnits;

        ImU32 color = IM_COL32_WHITE;
        PixelUnits thickness;
        typename LineElement<Origin, TDrawList, PixelsSymbol>::Vector2Ori start;
        typename LineElement<Origin, TDrawList, PixelsSymbol>::Vector2Ori end;

        [[nodiscard]] std::vector<typename LineElement<Origin, TDrawList, PixelsSymbol>::Vector2Ori> getPolyline() const override {
            return {start, end};
        }

        void doRender(RenderContext &render) const override {
            render.drawLine(start, end, color, thickness);
        }
    };

}