#include "imgui_functions.h"

#include <Magnum/Magnum.h>

namespace render::imgui {

    void drawCircle(ImDrawList &drawList, const Vector2Px &center, math::Pixels radius, ImU32 color, math::Pixels thickness) {
        drawList.AddCircle(center, (float) radius, color, 0, (float) thickness);
    }

    void drawLine(ImDrawList &drawList, const Vector2Px &start, const Vector2Px &end, ImU32 color, math::Pixels thickness) {
        drawList.AddLine(start, end, color, (float) thickness);
    }
}
