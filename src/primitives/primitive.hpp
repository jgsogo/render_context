#pragma once

#include "../render/context.h"

namespace primitives {
    using RenderContext = render::imgui::Context<math::types::MilimetersT>;
    using Vector2Mm = Magnum::Math::Vector2<math::Milimeters>;

    struct Primitive {
        virtual void doRender(RenderContext &render) const = 0;
    };

}