#pragma once

#include "primitive.hpp"

namespace primitives {

    template<const char *Origin, typename TDrawList>
    struct BasePolygon : Primitive<Origin, TDrawList> {
        bool filled = true;
        ImU32 fillColor = IM_COL32_BLACK;
        bool border = true;
        ImU32 borderColor = IM_COL32(255, 0, 0, 255);
        math::Pixels borderThickness{1.f};
    };

}