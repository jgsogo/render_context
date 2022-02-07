#pragma once

#include "../units/milimeters.hpp"
#include "../render/context.h"

namespace primitives {

    template<const char *Origin, typename TDrawList, const char *PixelsSymbol>
    struct Primitive {
        using RenderContext = render::Context<Origin, TDrawList, PixelsSymbol>;
        using Vector2Ori = typename RenderContext::Vector2Ori;

        virtual void doRender(RenderContext &render) const = 0;
    };

}