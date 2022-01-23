#pragma once

#include "../units/milimeters.hpp"
#include "../render/imgui/context.h"

namespace primitives {

    template<const char *Origin, typename TDrawList>
    struct Primitive {
        using RenderContext = render::Context<Origin, TDrawList>;
        using Vector2Ori = typename RenderContext::Vector2Ori;

        virtual void doRender(RenderContext &render) const = 0;
    };

}