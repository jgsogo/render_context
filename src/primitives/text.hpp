#pragma once

#include "primitive.hpp"


namespace primitives {

    template<const char *Origin, typename TDrawList>
    struct Text : Primitive<Origin, TDrawList> {
        using RenderContext = typename Primitive<Origin, TDrawList>::RenderContext;
        using Vector2Ori = typename RenderContext::Vector2Ori;

        ImU32 color = IM_COL32_BLACK;
        float fontSize = 8.f; // {ImGui::GetFontSize()};
        math::xy::types::Transformation<Origin, Origin, float> position;
        std::string content;

        void doRender(RenderContext &render) const override {
            render.drawText(position.transformPoint(Vector2Ori{Magnum::Math::ZeroInit}), fontSize, color, content);
        }
    };
}
